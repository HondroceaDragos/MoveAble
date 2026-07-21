#pragma once

#include "../entities/player.hpp"
#include "../graphics/buffer.hpp"

#include <cmath>

/* I need to define these in terms of buffer.x */
namespace universal {
    constexpr double maximum_momentum = 90.0;
    constexpr double friction = 120.0;
    constexpr double elasticity = 1.75;
}

class Engine {
public:
    Engine(const double& _dt);

    void updatePlayer(Player& p, Buffer& b);
private:
    double _dt;

    void _interpretInput(Player& p);
    void _normalizeDirection(double& dx, double& dy);
    void _clampPlayer(Player& p, Buffer& b);
    void _carryMomentum(Player& p);
};