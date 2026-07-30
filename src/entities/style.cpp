#include "../../include/entities/style.hpp"

Style::Style() {
    _points = points::base;
}

void Style::increasePoints(const bool& condition) {
    if (condition) _points += points::per_wall;
}

void Style::decreasePoints(const bool& condition) {
    if (condition) _points = std::fmax(points::base, _points -= points::decay_rate);
}

const double& Style::getPoints() const {
    return _points;
}

const std::string Style::getGrade() const {
    if (_points >= threshold::grade_s) return "S";
    if (_points >= threshold::grade_a) return "A";
    return "D";
}
