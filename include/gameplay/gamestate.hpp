#pragma once

class GameMaster;

class GameState {
public:
    virtual void onEnter(GameMaster& master) = 0;
    virtual void onExit(GameMaster& master) = 0;
    virtual void update(GameMaster& master) = 0;
    virtual void draw(GameMaster& master) = 0;
protected:
};
