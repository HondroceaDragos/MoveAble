#pragma once

#include "./entity.hpp"
#include "./style.hpp"
#include "../physics/ringbuffer.hpp"

#include <queue>

class Player: public Entity {
public:
    Player(const Vector2& position, const Hitbox& hitbox,
        const Vector2& velocity,
        const Vector2& momentum,
        const Sprite& sprite
    );

    void setStyle(const Style& newStyle);
    const Style& getStyle() const;

    void setTimeSinceWallHit(double t);
    const double& getTimeSinceWallHit() const;

    void logNewPosition();
    const RingBuffer<Vector2>& getPositionHistory() const;
private:
    Style _style;
    double _timeSinceWallHit;
    RingBuffer<Vector2> _position_history;
};
