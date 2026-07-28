#include "../../include/gameplay/playstate.hpp"
#include "../../include/gameplay/master.hpp"

PlayState::PlayState() {}
PlayState::~PlayState() {}

void PlayState::_updatePlayer(GameMaster& master) {
    auto& _engine = master.getEngine();
    auto& _player = master.getPlayer();
    auto& _buffer = master.getBuffer();

    _engine.updatePlayer(_player, _buffer);
}

void PlayState::_drawPlayer(GameMaster& master, const bool& showHitbox) {
    auto& _renderer = master.getRenderer();
    auto& _player = master.getPlayer();

    _renderer.drawPlayerSprite(_player);

    if (showHitbox) { _renderer.drawPlayerHitbox(_player); }
}

void PlayState::_drawGameplayBackground(GameMaster& master) {
    auto& _renderer = master.getRenderer();
    auto& _player = master.getPlayer();
    auto& _buffer = master.getBuffer();

    _renderer.drawGameplayBackground(_player.getStyle(), _buffer);
}

void PlayState::onEnter(GameMaster& master) { return; }
void PlayState::onExit(GameMaster& master) { return; }

void PlayState::_requestPause(GameMaster& master) {
    if (IsKeyPressed(KEY_P)) { master.changeState("pause"); }
}

void PlayState::update(GameMaster& master) {
    _requestPause(master);
    _updatePlayer(master);
}

void PlayState::draw(GameMaster& master) {
    BeginDrawing();
    _drawGameplayBackground(master);
    _drawPlayer(master, true);
    EndDrawing();
}
