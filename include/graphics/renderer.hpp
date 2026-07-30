#pragma once

#include "../entities/player.hpp"

#include <unordered_map>
#include <string>
#include <raylib.h>
#include <stdint.h>

#include "./buffer.hpp"

namespace fade {
    constexpr double duration = 2.5;
}

class Renderer {
public:
    Renderer();

    void drawPlayerSprite(const Player& p);
    void drawPlayerHitbox(const Player& p);
    void drawPlayerTrail(const Player& p);

    const Font& getFont(const std::string& where) const;

    void drawGameplayBackground(const Style& s, const Buffer& b);
    void drawFilter(const Buffer& b, const Color color);
private:
    std::unordered_map<std::string, Font> _fonts;
    void _drawEntitySprite(const Sprite& sprite, const Vector2& position, const double& scale, const Color& tint);
};
