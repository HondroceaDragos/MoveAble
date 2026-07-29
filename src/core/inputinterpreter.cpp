#include "../../include/core/inputinterpreter.hpp"

InputInterpreter::InputInterpreter() {}

Vector2 InputInterpreter::requestPlayerMovement() {
    Vector2 direction = {0};

    if (IsKeyDown(KEY_D)) { direction.x += 1.0;  }
    if (IsKeyDown(KEY_A)) { direction.x += -1.0; }
    if (IsKeyDown(KEY_W)) { direction.y += -1.0; }
    if (IsKeyDown(KEY_S)) { direction.y += 1.0;  }

    return direction;
}

bool InputInterpreter::requestPause() const {
    if (IsKeyPressed(KEY_P)) return true;
    return false;
}

bool InputInterpreter::requestAirTrick() const {
    if (IsKeyDown(KEY_SPACE)) return true;
    return false;
}
