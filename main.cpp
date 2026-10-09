#include "./include/gameplay/master.hpp"
// #include "./include/entities/player.hpp"
// #include "./include/graphics/buffer.hpp"
// #include "./include/core/engine.hpp"
// #include "./include/graphics/renderer.hpp"

int main(void) {
    Buffer buffer = Buffer();
    buffer.init("Moveable");

    auto [bufferWidth, bufferHeight] = buffer.getDimensions();

    double player_data = std::sqrtf(bufferHeight * bufferHeight + bufferWidth * bufferWidth);
    Player player = Player(
        (Vector2){bufferWidth / 2.0, bufferHeight / 2.0},
        (CircleHitbox){.center = (Vector2){bufferWidth / 2.0, bufferHeight / 2.0}, .radius = player_data / 32.0},
        (Vector2){player_data / 2.7, player_data / 2.7},
        (Vector2){0.0, 0.0},
        Sprite(LoadTexture("egg.png"), 0.0, player_data / 256.0 * 0.02)
    );

    Engine engine = Engine(0.0);
    Renderer renderer = Renderer();
    InputInterpreter input_interpreter = InputInterpreter();

    GameMaster gm = GameMaster(player, engine, renderer, buffer, input_interpreter);

    while (gm.active()) {
        gm.update();
        gm.draw();
    }

    buffer.deinit();
    return 0;
}