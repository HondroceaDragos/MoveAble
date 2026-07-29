#pragma once

#include "../entities/player.hpp"

#include <unordered_map>
#include <string>
#include <raylib.h>
#include <stdint.h>

#include "./buffer.hpp"

class Renderer {
public:
    Renderer();

    void drawPlayerSprite(const Player& p);
    void drawPlayerHitbox(const Player& p);

    const Font& getFont(const std::string& where) const;

    void drawGameplayBackground(const Style& s, const Buffer& b);
    void drawFilter(const Buffer& b, const Color color);
private:
    std::unordered_map<std::string, Font> _fonts;
};
