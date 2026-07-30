#include "../../include/graphics/renderer.hpp"

Renderer::Renderer() {
    _fonts = {
        {"gameplayBackground", LoadFontEx("./gameplayBackground.otf", 512, nullptr, 0)}
    };
}

void Renderer::_drawEntitySprite(const Sprite& sprite, const Vector2& position, const double& scale, const Color& tint) {
    Texture2D pt = sprite.getTexture();
    double tr = sprite.getRotation();

    auto [dx, dy] = position;

    double width = pt.width;
    double height = pt.height;

    double scaled_width = width * scale;
    double scaled_height = height * scale;

    Rectangle src = (Rectangle){0.0, 0.0, width, height};
    Rectangle dst = (Rectangle){dx, dy, scaled_width, scaled_height};
    Vector2 origin = {scaled_width / 2.0, scaled_height / 2.0};

    DrawTexturePro(pt, src, dst, origin, tr, tint);
}

void Renderer::drawPlayerSprite(const Player& p) {
    Sprite ps = p.getSprite();
    _drawEntitySprite(ps, p.getPosition(), ps.getScale(), RAYWHITE);
}

void Renderer::drawPlayerHitbox(const Player& p) {
    auto [dx, dy] = p.getPosition();
    double pr = std::get<CircleHitbox>(p.getHitbox()).radius;

    DrawCircle(dx, dy, pr, (Color){255, 0, 0, 128});
}

void Renderer::drawPlayerTrail(const Player& p) {
    auto grade = p.getStyle().getGrade();
    if (grade == "D") return;

    auto& position_history = p.getPositionHistory();
    if (position_history.size() == 0) return;

    Sprite ps = p.getSprite();

    size_t trail_count = 0;
    if (grade == "S") trail_count = 19;
    if (grade == "A") trail_count = 17;

    auto [dx, dy] = p.getPosition();
    auto [mx, my] = p.getMomentum();

    for (size_t copy = 1; copy <= trail_count; copy++) {
        double offset = 0.8 * copy;

        Vector2 copyPosition = position_history.at(offset);
        int32_t copyAlpha = static_cast<int32_t>(255 / (copy * 0.8));

        _drawEntitySprite(ps, copyPosition, ps.getScale() * 0.875, (Color){230, 230, 230, copyAlpha});
    }
}

const Font& Renderer::getFont(const std::string& where) const {
    return _fonts.at(where);
}

void Renderer::drawGameplayBackground(const Style& s, const Buffer& b) {
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

    auto grade = s.getGrade();

    ClearBackground((Color){230, 230, 230, 10});
    /* Dummy values - two wall hits = S, one wall hit = A, none = D */
    if (grade == "S") {
        drawGrade(grade, (Color){240, 32, 16, 64});
    } else if (grade == "A") {
        drawGrade(grade, (Color){32, 240, 16, 64});
    } else {
        drawGrade(grade, (Color){16, 32, 240, 64});
    }
}

void Renderer::drawFilter(const Buffer& b, const Color color) {
    auto& [bx, by] = b.getDimensions();
    DrawRectangle(0, 0, bx, by, color);
}
