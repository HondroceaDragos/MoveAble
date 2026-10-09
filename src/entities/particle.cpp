#include "../../include/entities/particle.hpp"

Particle::Particle() : Entity(), _lifetime(0.0), _maxlife(0.0) {}
Particle::~Particle() {}

Particle::Particle(
    const Vector2& position,
    const Hitbox& hitbox,
    const Vector2& velocity,
    const Vector2& momentum,
    const Sprite& sprite,
    double lifetime
): Entity(position, hitbox, velocity, momentum, sprite),
_lifetime(lifetime), _maxlife(lifetime)
{}

const double Particle::getLifetime() const { return _lifetime; }
void Particle::setLifetime(double lifetime) { _lifetime = lifetime; }

const double Particle::getMaxlife() const { return _maxlife; }
