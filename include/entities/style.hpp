#pragma once

#include <cmath>

namespace points {
    constexpr double base = 1.0;
    constexpr double per_wall = 4.25;
    constexpr double decay_rate = 1.25;
    constexpr double decay_delay = 1.5;
}

class Style {
public:
    Style();

    void increasePoints(const bool& condition);
    void decreasePoints(const bool& condition);

    const double& getPoints() const;
private:
    double _points;

};