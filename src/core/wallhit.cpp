#include "../../include/core/wallhit.hpp"

WallHit::WallHit() {}

void WallHit::registerHit(const std::string& side, const bool& truth) {
    _hits[side] = truth;
}

bool WallHit::inspectHit(const std::string& side) const {
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
