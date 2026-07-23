#include "../../include/core/engine.hpp"

Engine::Engine(const double& dt): _dt(dt) {}

void Engine::_normalizeDirection(Vector2& direction) {
    auto [dx, dy] = direction;
    double norm = std::sqrt(dx * dx + dy * dy);
    if (norm > 0.0) {
        dx /= norm;
        dy /= norm;
    }
    direction.x = dx;
    direction.y = dy;
}

void Engine::_normalizeMomentum(Vector2& momentum, const double& cap) {
    auto [mx, my] = momentum;
    double norm = std::sqrt(mx * mx + my * my);
    if (norm > cap) {
        norm = cap / norm;
        mx *= norm;
        my *= norm;
    }
    momentum.x = mx;
    momentum.y = my;
}

void Engine::_interpretInput(Player& p) {
    double vx = p.getVelocity().x;
    double vy = p.getVelocity().y;

    double mx = p.getMomentum().x;
    double my = p.getMomentum().y;

    Vector2 direction = {0};
    if (IsKeyDown(KEY_D)) { direction.x += 1.0;  }
    if (IsKeyDown(KEY_A)) { direction.x += -1.0; }
    if (IsKeyDown(KEY_W)) { direction.y += -1.0; }
    if (IsKeyDown(KEY_S)) { direction.y += 1.0;  }

    // if (IsKeyDown(KEY_SPACE)) {
    // }

    _normalizeDirection(direction);

    Vector2 addedMomentum = {direction.x * vx * _dt, direction.y * vy * _dt};
    _normalizeMomentum(addedMomentum, universal::maximum_input_momentum);

    mx += addedMomentum.x;
    my += addedMomentum.y;

    Vector2 momentum = {mx, my};
    _normalizeMomentum(momentum, universal::maximum_global_momentum);

    mx = momentum.x;
    my = momentum.y;

    p.setMomentum((Vector2){mx, my});
}

WallHit Engine::_checkWallCollision(Player& p, Buffer &b) {
    double dx = p.getPosition().x;
    double dy = p.getPosition().y;

    double pr = std::get<CircleHitbox>(p.getHitbox()).radius;

    auto [bx, by] = b.getDimensions();

    WallHit wh = WallHit();
    
    wh.registerHit("right", !(dx + pr <= bx));
    wh.registerHit("left", !(dx - pr >= 0));
    wh.registerHit("top", !(dy - pr >= 0));
    wh.registerHit("bottom", !(dy + pr <= by));
    
    return wh;
}

void Engine::_computeStyle(Player &p, WallHit& wh) {
    p.setStyle(wh.anyHits(), _dt);
}

void Engine::_clampPlayer(Player& p, Buffer& b, WallHit& wh) {
    double dx = p.getPosition().x;
    double dy = p.getPosition().y;

    auto [mx, my] = p.getMomentum();

    double pr = std::get<CircleHitbox>(p.getHitbox()).radius;

    auto [bx, by] = b.getDimensions();

    double stylePts = p.getStyle().getPoints();

    if (wh.inspectHit("right")) { dx = bx - pr; mx = -mx * universal::elasticity * stylePts; }
    if (wh.inspectHit("left"))  { dx = 0 + pr; mx = -mx * universal::elasticity * stylePts;  }
    if (wh.inspectHit("top"))  { dy = 0 + pr; my = -my * universal::elasticity * stylePts;  }
    if (wh.inspectHit("bottom")) { dy = by - pr; my = -my * universal::elasticity * stylePts; }

    p.setPosition((Vector2){dx, dy});
    p.setMomentum((Vector2){mx, my});
}

void Engine::_carryMomentum(Player& p) {
    auto [dx, dy] = p.getPosition();
    auto [mx, my] = p.getMomentum();
    p.setPosition((Vector2){dx + mx * _dt, dy + my * _dt});

    if (mx > 0.0) { mx = std::fmax(0.0, mx - universal::friction * _dt);
    } else if (mx < 0.0) { mx = fmin(0.0, mx + universal::friction * _dt); }

    if (my > 0.0) { my = fmax(0.0, my - universal::friction * _dt);
    } else if (my < 0.0) { my = fmin(0.0, my + universal::friction * _dt); }

    p.setMomentum((Vector2){mx, my});
}

void Engine::updatePlayer(Player& p, Buffer& b) {
    _dt = GetFrameTime();
    _interpretInput(p);
    _carryMomentum(p);

    WallHit wh = _checkWallCollision(p, b);
    _computeStyle(p, wh);
    _clampPlayer(p, b, wh);
}
