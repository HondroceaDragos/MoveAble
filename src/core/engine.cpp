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

void Engine::_normalizeMomentum(Vector2& momentum) {
    auto [mx, my] = momentum;
    double norm = std::sqrt(mx * mx + my * my);
    if (norm > universal::maximum_momentum) {
        norm = universal::maximum_momentum / norm;
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

    mx += direction.x * vx * _dt;
    my += direction.y * vy * _dt;
    Vector2 momentum = {mx, my};

    _normalizeMomentum(momentum);

    mx = momentum.x;
    my = momentum.y;

    p.setMomentum((Vector2){mx, my});
}

void Engine::_computeStyle(Player &p, Buffer& b) {
    double dx = p.getPosition().x;
    double dy = p.getPosition().y;

    auto [bx, by] = b.getDimensions();

    double pr = std::get<CircleHitbox>(p.getHitbox()).radius;

    double ammount = 1.0;
    if (!(dx + pr <= bx)) { ammount += 0.15; }
    if (!(dx - pr >= 0))  { ammount += 0.15; }
    if (!(dy - pr >= 0))  { ammount += 0.15; }
    if (!(dy + pr <= by)) { ammount += 0.15; }

    p.setStyle(ammount);
}

void Engine::_clampPlayer(Player &p, Buffer &b) {
    double dx = p.getPosition().x;
    double dy = p.getPosition().y;

    auto [mx, my] = p.getMomentum();

    double pr = std::get<CircleHitbox>(p.getHitbox()).radius;

    auto [bx, by] = b.getDimensions();

    double style = p.getStyle();

    if (!(dx + pr <= bx)) { dx = bx - pr; mx = -mx * universal::elasticity; }
    if (!(dx - pr >= 0))  { dx = 0 + pr; mx = -mx * universal::elasticity;  }
    if (!(dy - pr >= 0))  { dy = 0 + pr; my = -my * universal::elasticity;  }
    if (!(dy + pr <= by)) { dy = by - pr; my = -my * universal::elasticity; }

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
    _computeStyle(p, b);
    _clampPlayer(p, b);
}
