#include "../../include/gameplay/master.hpp"

GameMaster::GameMaster(const Player &player, const Engine &engine, const Renderer &renderer, const Buffer& buffer):
    _player(player), _engine(engine), _renderer(renderer), _shouldRun(false), _buffer(buffer) {}

void GameMaster::updatePlayer() { _engine.updatePlayer(_player, _buffer); }

void GameMaster::drawPlayer(const bool& showHitbox) {
    _renderer.drawPlayerSprite(_player);

    if (showHitbox) { _renderer.drawPlayerHitbox(_player); }
}

bool GameMaster::active() { return !WindowShouldClose(); }

void GameMaster::drawGameplayBackground() {
    _renderer.drawGameplayBackground(_player.getStyle(), _buffer);
}
