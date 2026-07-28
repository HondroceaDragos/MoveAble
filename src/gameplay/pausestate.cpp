#include "../../include/gameplay/pausestate.hpp"
#include "../../include/gameplay/master.hpp"

PauseState::PauseState() {}
PauseState::~PauseState() {}

void PauseState::_drawPlayer(GameMaster& master, const bool& showHitbox) {
    auto& _renderer = master.getRenderer();
    auto& _player = master.getPlayer();

    _renderer.drawPlayerSprite(_player);

    if (showHitbox) { _renderer.drawPlayerHitbox(_player); }
}

void PauseState::_drawGameplayBackground(GameMaster& master) {
    auto& _renderer = master.getRenderer();
    auto& _player = master.getPlayer();
    auto& _buffer = master.getBuffer();

    _renderer.drawGameplayBackground(_player.getStyle(), _buffer);
}

void PauseState::onEnter(GameMaster& master) { return; }
void PauseState::onExit(GameMaster& master) { return; }

void PauseState::_requestUnpause(GameMaster& master) {
    if (IsKeyPressed(KEY_P)) { master.changeState("play"); }
}

void PauseState::update(GameMaster& master) {
    _requestUnpause(master);
}

void PauseState::draw(GameMaster& master) {
        auto& _buffer = master.getBuffer();

    auto& [bx, by] = _buffer.getDimensions();
    BeginDrawing();
    _drawGameplayBackground(master);
    _drawPlayer(master, true);
    DrawRectangle(0, 0, bx, by, (Color){0, 240, 15, 64});
    EndDrawing();
}
