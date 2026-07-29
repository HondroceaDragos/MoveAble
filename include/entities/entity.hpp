#pragma once

#include "../physics/hitbox.hpp"
#include "../graphics/sprite.hpp"

class Entity {
public:
    Entity(const Vector2& position, const Hitbox& hitbox,
        const Vector2& velocity,
        const Vector2& momentum,
        const Sprite& sprite
    );
    Entity();

    void setPosition(const Vector2& newPosition);
    const Vector2& getPosition() const;
    
    void setMomentum(const Vector2& newMomentum);
    const Vector2& getMomentum() const;

    // setVelocity()
    const Vector2& getVelocity() const;

    const Hitbox& getHitbox() const;

    const Sprite& getSprite() const;

    const double& getOrientation() const;
    void setOrientation(const double& newOrientation);
    void setSpriteRotation(const double& newRotation);
protected:
    Vector2 _position;
    Vector2 _velocity;
    Vector2 _momentum;

    Hitbox _hitbox;
    Sprite _sprite;

    double _orientation;
};
