#include "../../include/core/vectorops.hpp"

Vector2 operator+(const Vector2& a, const Vector2& b) {
    return (Vector2){a.x + b.x, a.y + b.y};
}

Vector2 operator-(const Vector2& a, const Vector2& b) {
    return (Vector2){a.x - b.x, a.y - b.y};
}

double operator*(const Vector2& a, const Vector2& b) {
    return a.x * b.x + a.y * b.y;
}

Vector2 operator*(const Vector2& a, const double& scalar) {
    return (Vector2){a.x * scalar, a.y * scalar};
}

Vector2 operator*(const double& scalar, const Vector2& a) {
    return (Vector2){scalar * a.x, scalar * a.y};
}

Vector2 operator*=(Vector2& a, const double& scalar) {
    return a * scalar;
}
