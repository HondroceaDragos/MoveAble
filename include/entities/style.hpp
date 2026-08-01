#pragma once

#include <cmath>
#include <string>

namespace points {
    constexpr double base = 1.0;
    constexpr double per_wall = 4.25;
    constexpr double decay_rate = 1.0;
    constexpr double decay_delay = 1.15;
}

namespace threshold {
    constexpr double grade_s = 2 * points::per_wall;
    constexpr double grade_a = 1 * points::per_wall;
}

class Style {
public:
    Style();

    void increasePoints(const bool& condition);
    void decreasePoints(const bool& condition);

    const double& getPoints() const;
    const std::string getGrade() const;
private:
    double _points;

};
