#pragma once

#include <raylib.h>

static inline Vector2 operator+(const Vector2& a, const Vector2& b);
static inline Vector2 operator-(const Vector2& a, const Vector2& b);

/* Dot product */
static inline double operator*(const Vector2& a, const Vector2& b);

static inline Vector2 operator*(const Vector2& a, const double& scalar);
static inline Vector2 operator*(const double& scalar, const Vector2& a);
static inline Vector2 operator*=(const Vector2& a, const double& scalar);
