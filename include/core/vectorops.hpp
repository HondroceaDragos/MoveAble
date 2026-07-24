#pragma once

#include <raylib.h>

Vector2 operator+(const Vector2& a, const Vector2& b);
Vector2 operator-(const Vector2& a, const Vector2& b);

/* Dot product */
double operator*(const Vector2& a, const Vector2& b);

Vector2 operator*(const Vector2& a, const double& scalar);
Vector2 operator*(const double& scalar, const Vector2& a);
Vector2 operator*=(Vector2& a, const double& scalar);
