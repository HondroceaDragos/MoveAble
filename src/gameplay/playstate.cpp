#include "../../include/gameplay/playstate.hpp"
#include "../../include/gameplay/master.hpp"

#include "../../include/physics/randomizer.hpp"

/* This SHOULD REALLY BE A FACTORY */
PlayState::PlayState() {
    _eggshell = LoadTexture("shell.png");
}
PlayState::~PlayState() {
    UnloadTexture(_eggshell);
}

void PlayState::_emitParticles(GameMaster &master, const WallHit& wh) {
    auto& pe = master.getParticleEngine();

    for (const auto& side : {"left", "right", "top", "bottom"}) {
        if (!wh.inspectHit(side)) continue;

        auto norm = wh.getWallNormal(side);
        const size_t pcount = pe.capacity();

        /* Magic eggshells uwu */
        for (size_t idx = 0; idx < 6; idx++) {
            double pangle = atan2(norm.y, norm.x) + Randomizer(-0.8, 0.8).getValue();
            double pspeed = Randomizer(200.0, 450.0).getValue();

            Vector2 pvel = {
                cos(pangle) * pspeed,
                sin(pangle) * pspeed
            };

            Vector2 playerPos = master.getPlayer().getPosition();

            /* Should be a player deadzone - add later */
            Vector2 ppos = {
                playerPos.x + Randomizer(-16.0, 16.0).getValue(),
                playerPos.y + Randomizer(-8.0, 8.0).getValue()
            };

            Particle p(
                ppos,
                (CircleHitbox){.radius = 32.0},
                pvel,
                Vector2{0.0, 0.0},
                Sprite(_eggshell, Randomizer(0.0, 360.0).getValue(), master.getPlayer().getSprite().getScale() * 30.0),
                Randomizer(0.3, 0.8).getValue()
            );

            pe.record(p);
        }
    }
}

void PlayState::_updateParticles(GameMaster &master) {
    auto& pe = master.getParticleEngine();
    auto& engine = master.getEngine();

    for (size_t idx = 0; idx < pe.size(); idx++) {
        engine.updateParticle(pe.at(idx));
    }
}

void PlayState::_updatePlayer(GameMaster& master) {
    auto& _engine = master.getEngine();
    auto& _player = master.getPlayer();
    auto& _buffer = master.getBuffer();
    auto& _input_interpreter = master.getInputInterpreter();

    auto direction = _input_interpreter.requestPlayerMovement();
    auto spinning = _input_interpreter.requestAirTrick();

    WallHit wh = _engine.updatePlayer(_player, _buffer, direction, spinning);
    if (wh.anyHits()) _emitParticles(master, wh);
}

void PlayState::_drawPlayer(GameMaster& master, const bool& showHitbox) {
    auto& _renderer = master.getRenderer();
    auto& _player = master.getPlayer();

    _renderer.drawPlayerTrail(_player);
    _renderer.drawPlayerSprite(_player);

    if (showHitbox) { _renderer.drawPlayerHitbox(_player); }
}

void PlayState::_drawGameplayBackground(GameMaster& master) {
    auto& _renderer = master.getRenderer();
    auto& _player = master.getPlayer();
    auto& _buffer = master.getBuffer();

    _renderer.drawGameplayBackground(_player.getStyle(), _buffer);
}

void PlayState::_drawParticles(GameMaster &master) {
    auto& pe = master.getParticleEngine();
    auto& r = master.getRenderer();

    for (size_t idx = 0; idx < pe.size(); idx++) {
        const auto& p = pe.at(idx);
        if (p.getLifetime() > 0.0) {
            // r.drawParticleHitbox(p);
            r.drawParticleSprite(p);
        }
    }
}

void PlayState::onEnter(GameMaster& master) { return; }
void PlayState::onExit(GameMaster& master) { return; }

void PlayState::_requestPause(GameMaster& master) {
    if (master.getInputInterpreter().requestPause()) { master.changeState("pause"); }
}

void PlayState::update(GameMaster& master) {
    _requestPause(master);
    _updatePlayer(master);
    _updateParticles(master);
}

void PlayState::draw(GameMaster& master) {
    BeginDrawing();

    _drawGameplayBackground(master);
    _drawPlayer(master, false);
    _drawParticles(master);

    /* Should know about buffer - ok for dirty work */
    DrawFPS(10, 10);

    EndDrawing();
}
