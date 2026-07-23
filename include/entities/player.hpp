#pragma once

#include "./entity.hpp"
#include "./style.hpp"

class Player: public Entity {
public:
    Player(const Vector2& position, const Hitbox& hitbox,
        const Vector2& velocity,
        const Vector2& momentum,
        const Sprite& sprite
    );

    void setStyle(const bool& condition, const double& dt);
    const Style& getStyle() const;
private:
    Style _style;
    double _timeSinceWallHit;
};
