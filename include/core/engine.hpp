#pragma once

#include "../entities/player.hpp"
#include "../graphics/buffer.hpp"

#include <cmath>

/* I need to define these in terms of buffer.x */
namespace universal {
    constexpr double maximum_momentum = 500.0;
    constexpr double friction = 23.0;
    constexpr double elasticity = 0.8;
}

class Engine {
public:
    Engine(const double& _dt);

    void updatePlayer(Player& p, Buffer& b);
private:
    double _dt;

    void _interpretInput(Player& p);
    void _normalizeDirection(Vector2& direction);
    void _normalizeMomentum(Vector2& momentum);
    void _clampPlayer(Player& p, Buffer& b);
    void _carryMomentum(Player& p);
    void _computeStyle(Player &p, Buffer& b);
};