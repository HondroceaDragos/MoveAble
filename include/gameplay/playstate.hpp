#pragma once

#include "./gamestate.hpp"
#include "../../include/core/wallhit.hpp"

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
    void _emitParticles(GameMaster &master, const WallHit& wh);
    void _updateParticles(GameMaster &master);

    void _drawPlayer(GameMaster& master, const bool& showHitbox);
    void _drawParticles(GameMaster &master);
    void _drawGameplayBackground(GameMaster& master);

    void _requestPause(GameMaster& master);

    Texture2D _eggshell;
};
