#include "../../include/physics/randomizer.hpp"

Randomizer::Randomizer() {}

Randomizer::Randomizer(const double start, const double stop): _value(start, stop) {
    std::random_device rd;
    auto seed = rd();
    _generator = std::mt19937_64(seed);
}

Randomizer::~Randomizer() {}

const double Randomizer::getValue() { return _value(_generator); }
