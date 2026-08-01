#pragma once

#include <unordered_map>
#include <string>
#include <stdint.h>
#include <raylib.h>

class WallHit {
public:
    WallHit();
    
    void registerHit(const std::string& side, const bool& truth);
    const bool& inspectHit(const std::string& side) const;
    int32_t countHits() const;
    bool anyHits() const;

    const Vector2& getWallNormal(const std::string& side) const;

    void setBounceAngle(double newAngle);
    const double& getBounceAngle() const;
private:
    std::unordered_map<std::string, bool> _hits;
    std::unordered_map<std::string, Vector2> _normals;

    double _bounce_angle;
};
