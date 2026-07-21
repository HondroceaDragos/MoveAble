#include "../../include/graphics/renderer.hpp"

Renderer::Renderer() {}

void Renderer::drawPlayerSprite(Player& p) {
    Sprite ps = p.getSprite();

    Texture2D pt = ps.getTexture();
    double tr = ps.getRotation();
    double ts = ps.getScale();

    auto [dx, dy] = p.getPosition();

    DrawTextureEx(
        pt,
        (Vector2){dx - pt.width * ts / 2, dy - pt.height * ts / 2},
        tr,
        ts,
        RAYWHITE
    );
}

void Renderer::drawPlayerHitbox(Player& p) {
    auto [dx, dy] = p.getPosition();
    double pr = std::get<CircleHitbox>(p.getHitbox()).radius;

    DrawCircle(dx, dy, pr, (Color){255, 0, 0, 128});
}
