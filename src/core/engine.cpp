#include "../../include/core/engine.hpp"

Engine::Engine(const double& dt): _dt(dt) {}

void _normalizeDirection(double& dx, double& dy) {
    double norm = std::sqrtf(dx * dx + dy * dy);
    if (norm > 0.0) {
        dx /= norm;
        dy /= norm;
    }
}

void Engine::_interpretInput(Player& p) {
    double dx = p.getPosition().x;
    double dy = p.getPosition().y;

    double vx = p.getVelocity().x;
    double vy = p.getVelocity().y;

    double mx = p.getMomentum().x;
    double my = p.getMomentum().y;

    if (IsKeyDown(KEY_D)) {
        dx += vx * _dt;
        mx = std::fmin(universal::maximum_momentum, mx + vx);
    }

    if (IsKeyDown(KEY_A)) {
        dx -= vx * _dt;
        mx = std::fmax(-universal::maximum_momentum, mx - vx);
    }

    if (IsKeyDown(KEY_W)) {
        dy -= vy * _dt;
        my = std::fmax(-universal::maximum_momentum, my - vy);
    }

    if (IsKeyDown(KEY_S)) {
        dy += vy * _dt;
        my = std::fmin(universal::maximum_momentum, my + vy);
    }

    // if (IsKeyDown(KEY_SPACE)) {
    // }
    

    p.setPosition((Vector2){dx, dy});
    p.setMomentum((Vector2){mx, my});
}

void Engine::_clampPlayer(Player &p, Buffer &b) {
    double dx = p.getPosition().x;
    double dy = p.getPosition().y;

    auto [mx, my] = p.getMomentum();

    double pr = std::get<CircleHitbox>(p.getHitbox()).radius;

    auto [bx, by] = b.getDimensions();

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
    _clampPlayer(p, b);
}
