#include "../../include/entities/entity.hpp"

Entity::Entity(const Vector2& position, const Hitbox& hitbox,
        const Vector2& velocity,
        const Vector2& momentum,
        const Sprite& sprite
    ):
    _position(position), _hitbox(hitbox),
    _velocity(velocity), _momentum(momentum),
    _sprite(sprite) {}

Entity::Entity() {}

void Entity::setPosition(const Vector2 &newPosition) { _position = newPosition; }
const Vector2& Entity::getPosition() const { return _position; }

void Entity::setMomentum(const Vector2 &newMomentum) { _momentum = newMomentum; }
const Vector2& Entity::getMomentum() const { return _momentum; }

const Vector2 &Entity::getVelocity() const { return _velocity; }

const Hitbox &Entity::getHitbox() const { return _hitbox; }

const Sprite &Entity::getSprite() const { return _sprite; }
