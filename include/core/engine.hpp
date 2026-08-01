#pragma once

#include "../entities/player.hpp"
#include "../graphics/buffer.hpp"
#include "./wallhit.hpp"
#include "./vectorops.hpp"
#include "../physics/randomizer.hpp"

#include <cmath>

/* I need to define these in terms of buffer.x */
namespace universal {
    constexpr double maximum_input_momentum = 815.0;
    constexpr double maximum_global_momentum = 1225.0;
    constexpr double friction = 41.0;
    constexpr double elasticity = 0.25;
    constexpr double centripetal = 270.0;
}

class Engine {
public:
    Engine(const double& _dt);

    void updatePlayer(Player& p, Buffer& b, Vector2& direction, const bool& spinning);
private:
    double _dt;
    Randomizer _bounce_angle;

    void _movePlayer(Player& p, Vector2& direction);
    void _normalizeDirection(Vector2& direction);
    void _normalizeMomentum(Vector2& momentum, const double& cap);

    void _spinPlayer(Player& p, const bool& spinning);

    WallHit _checkWallCollision(Player& p, Buffer &b);
    Vector2 _computeVectorReflection(const Vector2& v, const Vector2& normal) const;
    Vector2 _rotateVector(const Vector2& v, double angle) const;
    void _clampPlayer(Player& p, Buffer& b, WallHit& wh);
    void _computeStyle(Player &p, WallHit& wh);

    void _carryMomentum(Player& p);
};
