#pragma once

#include "./entity.hpp"

namespace pconts {
    constexpr double maxlife = 32.0;
}

class Particle: public Entity {
public:
    Particle();
    ~Particle();

    Particle(
        const Vector2& position,
        const Hitbox& hitbox,
        const Vector2& velocity,
        const Vector2& momentum,
        const Sprite& sprite,
        double lifetime = pconts::maxlife
    );

    const double getLifetime() const;
    void setLifetime(double lifetime);

    const double getMaxlife() const;
private:
    double _lifetime;
    double _maxlife;
};
