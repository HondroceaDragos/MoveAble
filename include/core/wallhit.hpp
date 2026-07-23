#pragma once

#include <unordered_map>
#include <string>
#include <stdint.h>

class WallHit {
public:
    WallHit();
    
    void registerHit(const std::string& side, const bool& truth);
    bool inspectHit(const std::string& side) const;
    int32_t countHits() const;
    bool anyHits() const;
private:
    std::unordered_map<std::string, bool> _hits;
};
