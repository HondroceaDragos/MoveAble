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

        this->_style = Style();
        this->_timeSinceWallHit = 0.0;

        this->_orientation = 0.0;
    }

void Player::setStyle(const bool& condition, const double& dt) {
    if (condition) {
        _timeSinceWallHit = 0.0;
        _style.increasePoints(condition);
    } else {
        _timeSinceWallHit += dt;
        _style.decreasePoints(_timeSinceWallHit >= points::decay_delay);
    }
}

const Style& Player::getStyle() const {
    return _style;
}
