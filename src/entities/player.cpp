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
        this->_position_history = RingBuffer<Vector2>(40);
    }

void Player::setStyle(const Style& newStyle) { _style = newStyle; }
const Style& Player::getStyle() const { return _style; }

void Player::setTimeSinceWallHit(double t) { _timeSinceWallHit = t; }
const double& Player::getTimeSinceWallHit() const { return _timeSinceWallHit; }

void Player::logNewPosition() { _position_history.record(_position); }
const RingBuffer<Vector2>& Player::getPositionHistory() const { return _position_history; }
