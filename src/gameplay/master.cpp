#include "../../include/gameplay/master.hpp"
#include "../../include/gameplay/playstate.hpp"
#include "../../include/gameplay/pausestate.hpp"

GameMaster::GameMaster(const Player &player, const Engine &engine, const Renderer &renderer,
    const Buffer& buffer, const InputInterpreter& i):
    _player(player), _engine(engine), _renderer(renderer), _shouldRun(false), _buffer(buffer), _input_interpreter(i) {
        _states["play"] = std::make_unique<PlayState>();
        _states["pause"] = std::make_unique<PauseState>();

        _currState = "play";
        _states.at(_currState)->onEnter(*this);
    }

bool GameMaster::active() { return !WindowShouldClose(); }

Player& GameMaster::getPlayer() { return _player; }
Engine& GameMaster::getEngine() { return _engine; }
Renderer& GameMaster::getRenderer() { return _renderer; }
Buffer& GameMaster::getBuffer() { return _buffer; }
InputInterpreter& GameMaster::getInputInterpreter() { return _input_interpreter; }

void GameMaster::changeState(const std::string& newState) {
    _states.at(_currState)->onExit(*this);
    _currState = newState;
    _states.at(_currState)->onEnter(*this);
}

void GameMaster::update() {
    _states.at(_currState)->update(*this);
}

void GameMaster::draw() {
    _states.at(_currState)->draw(*this);
}
