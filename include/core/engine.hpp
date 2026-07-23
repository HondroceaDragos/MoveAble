#pragma once

#include "../entities/player.hpp"
#include "../graphics/buffer.hpp"
#include "./wallhit.hpp"

#include <cmath>

/* I need to define these in terms of buffer.x */
namespace universal {
    constexpr double maximum_input_momentum = 615.0;
    constexpr double maximum_global_momentum = 950.0;
    constexpr double friction = 37.0;
    constexpr double elasticity = 0.45;
}

class Engine {
public:
    Engine(const double& _dt);

    void updatePlayer(Player& p, Buffer& b);
private:
    double _dt;

    void _interpretInput(Player& p);
    void _normalizeDirection(Vector2& direction);
    void _normalizeMomentum(Vector2& momentum, const double& cap);

    WallHit _checkWallCollision(Player& p, Buffer &b);
    void _clampPlayer(Player& p, Buffer& b, WallHit& wh);
    void _computeStyle(Player &p, WallHit& wh);

    void _carryMomentum(Player& p);
};
