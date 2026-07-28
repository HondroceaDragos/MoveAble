#pragma once

#include "./gamestate.hpp"

class PlayState : public GameState {
public:
    PlayState();
    ~PlayState();
    void onEnter(GameMaster& master) override;
    void onExit(GameMaster& master) override;
    void update(GameMaster& master) override;
    void draw(GameMaster& master) override;
private:
    void _updatePlayer(GameMaster& master);

    void _drawPlayer(GameMaster& master, const bool& showHitbox);
    void _drawGameplayBackground(GameMaster& master);

    void _requestPause(GameMaster& master);
};