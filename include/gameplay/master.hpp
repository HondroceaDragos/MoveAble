#pragma once

#include "../core/engine.hpp"
#include "../core/wallhit.hpp"
#include "../core/inputinterpreter.hpp"
#include "../entities/player.hpp"
#include "../entities/particle.hpp"
#include "../graphics/renderer.hpp"
#include "../graphics/buffer.hpp"

#include "./gamestate.hpp"

#include <unordered_map>
#include <string>
#include <memory>

class GameMaster {
public:
    GameMaster(const Player& player, const Engine& engine, const Renderer& renderer,
        const Buffer& buffer, const InputInterpreter& i);

    void update();
    void draw();

    Player& getPlayer();
    Engine& getEngine();
    Renderer& getRenderer();
    Buffer& getBuffer();
    InputInterpreter& getInputInterpreter();

    RingBuffer<Particle>& getParticleEngine();

    bool active();
    void changeState(const std::string& newState);
private:
    bool _shouldRun;

    Player _player;
    Engine _engine;
    Renderer _renderer;
    Buffer _buffer;
    InputInterpreter _input_interpreter;

    std::string _currState;
    std::unordered_map<std::string, std::unique_ptr<GameState>> _states;

    RingBuffer<Particle> _particleEngine;
};
