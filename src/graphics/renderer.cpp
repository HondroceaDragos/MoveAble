#include "../../include/graphics/renderer.hpp"

Renderer::Renderer() {
    _fonts = {
        {"gameplayBackground", LoadFontEx("./gameplayBackground.otf", 512, nullptr, 0)}
    };
}

void Renderer::drawPlayerSprite(const Player& p) {
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

void Renderer::drawPlayerHitbox(const Player& p) {
    auto [dx, dy] = p.getPosition();
    double pr = std::get<CircleHitbox>(p.getHitbox()).radius;

    DrawCircle(dx, dy, pr, (Color){255, 0, 0, 128});
}

const Font& Renderer::getFont(const std::string& where) const {
    return _fonts.at(where);
}

void Renderer::drawGameplayBackground(const Style& s, const Buffer& b) {
    double style_points = s.getPoints();
    auto [bx, by] = b.getDimensions();

    double grade_size = (bx / 3.0 + by / 3.0);

    Font gameplay_bkg_font = _fonts.at("gameplayBackground");
    double grade_spacing = gameplay_bkg_font.baseSize;

    auto drawGrade = [&](std::string grade, Color color) {
        Vector2 grade_dimensions = MeasureTextEx(gameplay_bkg_font, grade.c_str(), grade_size, grade_spacing);
        Vector2 grade_pos = {
            (bx - 0.90 * grade_dimensions.x) / 2,
            (by - 0.90 * grade_dimensions.y) / 2
        };
        DrawTextEx(gameplay_bkg_font, grade.c_str(), grade_pos, grade_size, grade_spacing, color);
    };

    ClearBackground((Color){230, 230, 230, 10});
    /* Dummy values - two wall hits = S, one wall hit = A, none = D */
    if (style_points >= 9.50) {
        drawGrade("S", (Color){240, 32, 16, 64});
    } else if (style_points >= 5.25) {
        drawGrade("A", (Color){32, 240, 16, 64});
    } else {
        drawGrade("D", (Color){16, 32, 240, 64});
    }
}
