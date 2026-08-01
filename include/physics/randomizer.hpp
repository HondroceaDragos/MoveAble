#pragma once

#include <random>

class Randomizer {
public:
    Randomizer();
    Randomizer(const double start, const double stop);
    ~Randomizer();

    const double getValue();
private:
    std::mt19937_64 _generator;
    std::uniform_real_distribution<double> _value;
};
