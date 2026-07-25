#pragma once

#include "../core/engine.hpp"
#include "../entities/player.hpp"
#include "../graphics/renderer.hpp"
#include "../graphics/buffer.hpp"

class GameMaster {
public:
    GameMaster(const Player& player, const Engine& engine, const Renderer& renderer, const Buffer& buffer);

    void updatePlayer();

    void drawPlayer(const bool& showHitbox);
    void drawGameplayBackground();

    bool active();
private:
    bool _shouldRun;

    Player _player;
    Engine _engine;
    Renderer _renderer;
    Buffer _buffer;
};