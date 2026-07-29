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

void PauseState::_drawPauseFilter(GameMaster& master) {
    auto& _buffer = master.getBuffer();
    master.getRenderer().drawFilter(_buffer, (Color){182, 182, 182, 128});
}

void PauseState::onEnter(GameMaster& master) { return; }
void PauseState::onExit(GameMaster& master) { return; }

void PauseState::_requestUnpause(GameMaster& master) {
    if (master.getInputInterpreter().requestPause()) { master.changeState("play"); }
}

void PauseState::update(GameMaster& master) {
    _requestUnpause(master);
}

void PauseState::draw(GameMaster& master) {
    BeginDrawing();
    _drawGameplayBackground(master);
    _drawPlayer(master, true);
    _drawPauseFilter(master);
    EndDrawing();
}
