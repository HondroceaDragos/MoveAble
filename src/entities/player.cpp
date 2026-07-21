#include "../../include/entities/player.hpp"

Player::Player(const Vector2& position, const Hitbox& hitbox,
        const Vector2& velocity,
        const Vector2& momentum,
        const Sprite& sprite
    ) {
        this->_position = position;
        this->_hitbox = hitbox;
        this->_velocity = velocity;
        this->_momentum = momentum;
        this->_sprite = sprite;
    }
