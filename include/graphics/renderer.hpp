#pragma once

#include "../entities/player.hpp"

class Renderer {
public:
    Renderer();
    void drawPlayerSprite(Player& p);
    void drawPlayerHitbox(Player& p);
private:
};
