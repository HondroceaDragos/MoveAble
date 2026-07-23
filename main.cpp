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
        Sprite(LoadTexture("sprite.png"), 0.0, 0.3)
    );

    Engine engine = Engine(0.0);
    Renderer renderer = Renderer();

    GameMaster gm = GameMaster(player, engine, renderer, buffer);

    while (gm.active()) {
        gm.updatePlayer();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        gm.drawPlayer(true);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}