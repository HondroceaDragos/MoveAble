#pragma once

#include <raylib.h>

class InputInterpreter {
public:
    InputInterpreter();

    Vector2 requestPlayerMovement();

    bool requestPause() const;
    bool requestAirTrick() const;
private:
};