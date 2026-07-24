#include "../../include/core/wallhit.hpp"

WallHit::WallHit() {
    _normals = {
        {"left", (Vector2){1.0, 0.0}},
        {"right", (Vector2){-1.0, 0.0}},
        {"top", (Vector2){0.0, 1.0}},
        {"bottom", (Vector2){0.0, -1.0}}
    };
}

void WallHit::registerHit(const std::string& side, const bool& truth) {
    _hits[side] = truth;
}

const bool& WallHit::inspectHit(const std::string& side) const {
    return _hits.at(side);
}

int32_t WallHit::countHits() const {
    int32_t hits = 0;
    for (auto& [k, v] : _hits) {
        hits += v;
    }
    return hits;
}

bool WallHit::anyHits() const {
    return countHits() > 0;
}

const Vector2& WallHit::getWallNormal(const std::string& side) const {
    return _normals.at(side);
}
