#pragma once

#include "./gamestate.hpp"

class PauseState : public GameState {
public:
    PauseState();
    ~PauseState();
    void onEnter(GameMaster& master) override;
    void onExit(GameMaster& master) override;
    void update(GameMaster& master) override;
    void draw(GameMaster& master) override;
private:
    void _drawPlayer(GameMaster& master, const bool& showHitbox);
    void _drawGameplayBackground(GameMaster& master);
    void _drawPauseFilter(GameMaster& master);

    void _drawParticles(GameMaster &master);

    void _requestUnpause(GameMaster& master);
};