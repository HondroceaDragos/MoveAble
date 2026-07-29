#include "../../include/core/engine.hpp"

#include <algorithm>

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

void Engine::_movePlayer(Player& p, Vector2& direction) {
    double vx = p.getVelocity().x;
    double vy = p.getVelocity().y;

    double mx = p.getMomentum().x;
    double my = p.getMomentum().y;

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

void Engine::_spinPlayer(Player& p, const bool& spinning) {
    if (!spinning) return;

    double newOrientation = p.getOrientation() + universal::centripetal * _dt;
    double angle = std::fmod(newOrientation, 360.0);

    p.setOrientation(angle);
    p.setSpriteRotation(angle);
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

const Vector2 Engine::_computeVectorReflection(const Vector2& v, const Vector2& normal) {
    return v - 2 * (v * normal) * normal;
}

void Engine::_clampPlayer(Player& p, Buffer& b, WallHit& wh) {
    double dx = p.getPosition().x;
    double dy = p.getPosition().y;

    auto [mx, my] = p.getMomentum();

    double pr = std::get<CircleHitbox>(p.getHitbox()).radius;

    auto [bx, by] = b.getDimensions();

    double stylePts = p.getStyle().getPoints();

    auto _bounce = [&](const Vector2& normal) {
        auto mp = _computeVectorReflection((Vector2){mx, my}, normal);
        mp *= universal::elasticity * stylePts;
        mx = mp.x;
        my = mp.y;
    };

    if (wh.inspectHit("right"))  { dx = bx - pr; _bounce(wh.getWallNormal("right"));  }
    if (wh.inspectHit("left"))   { dx =  0 + pr; _bounce(wh.getWallNormal("left"));   }
    if (wh.inspectHit("top"))    { dy =  0 + pr; _bounce(wh.getWallNormal("top"));    }
    if (wh.inspectHit("bottom")) { dy = by - pr; _bounce(wh.getWallNormal("bottom")); }

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

void Engine::updatePlayer(Player& p, Buffer& b, Vector2& direction, const bool& spinning) {
    _dt = GetFrameTime();
    _movePlayer(p, direction);
    _spinPlayer(p, spinning);
    _carryMomentum(p);

    WallHit wh = _checkWallCollision(p, b);
    _computeStyle(p, wh);
    _clampPlayer(p, b, wh);
}
