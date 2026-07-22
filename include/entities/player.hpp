#pragma once

#include "./entity.hpp"

class Player: public Entity {
public:
    Player(const Vector2& position, const Hitbox& hitbox,
        const Vector2& velocity,
        const Vector2& momentum,
        const Sprite& sprite
    );

    void setStyle(const double& newStyle);
    const double& getStyle() const;
private:
    double _style;
};