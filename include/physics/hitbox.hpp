#pragma once

#include <raylib.h>
#include <variant>

class CircleHitbox {
public:
    Vector2 center;
    double radius;
};

using Hitbox = std::variant<CircleHitbox>;