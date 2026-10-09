# MoveAble

[![Try out the demo](https://img.shields.io/badge/Try%20out%20the-demo-blue)](https://github.com/HondroceaDragos/MoveAble/releases/tag/v0.0.1)

**A small C++20 game engine built using [Raylib](https://www.raylib.com/), focused on arcade-style movement mechanics: an egg that bounces off the walls, builds momentum, and gets more stylish the more it hits.**

> Windows only. The build is configured for MinGW-w64 and the Win32 / OpenGL system libraries.

---

## Overview

MoveAble is a minimal, dependency-light game engine written in C++20 on top of Raylib. The game is split into small, focused components (window/buffer, entities, engine, renderer, input, game states) wired together by a single `GameMaster`, which owns the main loop and delegates updating and drawing to the active game state.

The core idea is *momentum and style*: the player is an egg that ricochets around the screen. Every wall hit reflects its momentum, and chaining hits in quick succession raises a **style** rating. Higher style means bouncier walls, a longer ghost trail, and a bigger grade letter behind the action.

## Controls

| Key | Action |
| --- | --- |
| <kbd>W</kbd> <kbd>A</kbd> <kbd>S</kbd> <kbd>D</kbd> | Move (diagonals are normalized) |
| <kbd>Space</kbd> (hold) | Spin the egg around its center (cosmetic only) |
| <kbd>P</kbd> | Pause / unpause |

## Features

### Movement and physics
- **Momentum-based movement**: input adds momentum, capped separately for input and for the total; friction slows the player when idle
- **Normalized direction and momentum**: consistent speed regardless of input direction
- **Reflective wall bounces**: the momentum vector is reflected across the wall normal instead of simply inverted
- **Bounce randomizer**: each wall hit rotates the normal by a small random angle (±3.5°) so paths don't repeat
- **Style-scaled bounces**: the energy kept after a bounce scales with the current style
- **Custom `Vector2` operations**: addition, subtraction, dot product, scalar multiplication (and multiplicative assignment)

### Style system
- **Style from wall hits**: wall hits add style points; style decays after a short delay without hits. The timing is tracked by the `Engine`
- **Grades**: points map to a grade (`S`, `A`, `D`), shown as a large color-coded letter in the background
- **Sprite trail**: the player's stats hold a generic ring buffer of recent positions; the renderer draws fading ghost copies behind the egg, with more ghosts at higher grades

### Particles
- **`Particle` extends `Entity`** and adds its own lifetime, used for fading and expiry
- **Gameplay-neutral**: particles carry circle hitboxes, but those are ignored and never affect gameplay
- **Eggshell burst**: each wall hit spawns 6 eggshell particles scattered around the player
- **Pseudo-random variation**: lifetime, rotation, speed and scale are randomized per particle
- **Normal-driven spread**: particles fly outward along the wall's normal vector
- **Ring-buffered pool**: particles live in a fixed-size ring buffer, so the oldest are recycled instead of allocating

### Game structure
- **Game states**: `play` and `pause`, switched through `GameMaster::changeState`; pausing dims the scene with a grey filter and shows hitboxes for debugging
- **`InputInterpreter`**: all user requests (movement, pause, spin) go through it, and states query it via `GameMaster`
- **Window setup**: `Buffer` opens a window at half the monitor's resolution, targets the monitor's refresh rate, and closes the window on application exit
- **Resolution-independent sizing**: the player's radius, speed and sprite scale are derived from the window diagonal

## Project Structure

```
MoveAble/
├── main.cpp                   # Entry point: builds the player and components, runs the loop
├── Makefile                   # Windows build (g++ / MinGW-w64)
├── include/
│   ├── core/                  # engine, inputinterpreter, vectorops, wallhit
│   ├── entities/              # entity, player, particle, style
│   ├── gameplay/              # master (GameMaster), gamestate, playstate, pausestate
│   ├── graphics/              # buffer, renderer, sprite
│   └── physics/               # hitbox, randomizer, ringbuffer
├── src/                       # Implementations, mirroring include/
├── egg.png                    # Player sprite
├── shell.png                  # Eggshell particle sprite
└── gameplayBackground.otf     # Font for the background grade letter
```

## Architecture

`main.cpp` constructs every component and hands them to `GameMaster`:

```cpp
Buffer buffer = Buffer();
buffer.init("Moveable");

Player player = Player(position, CircleHitbox{...}, velocity, momentum, Sprite{...});
Engine engine = Engine(0.0);
Renderer renderer = Renderer();
InputInterpreter input_interpreter = InputInterpreter();

GameMaster gm = GameMaster(player, engine, renderer, buffer, input_interpreter);

while (gm.active()) {
    gm.update();
    gm.draw();
}

buffer.deinit();
```

| Component | Role |
| --- | --- |
| `Buffer` | Creates the window, sets the target FPS, reports dimensions, closes the window on exit |
| `Entity` | Base for anything in the world: position, velocity, momentum, `Hitbox`, `Sprite`, orientation |
| `Player` | Extends `Entity` with `Style`, time since last wall hit, and a ring buffer of past positions |
| `Particle` | Extends `Entity` with a lifetime and max lifetime |
| `Style` | Style points, decay, and the point-to-grade mapping |
| `WallHit` | Per-frame record of which walls were hit, their normals, and the randomized bounce angle |
| `Engine` | Simulation: movement, spin, wall collision and reflection, style timing, particle motion |
| `Renderer` | Draws the background, player, trail, particles, hitboxes and the pause filter |
| `InputInterpreter` | Translates raw keys into movement, pause and spin requests |
| `GameState` (`PlayState`, `PauseState`) | Per-state `onEnter`, `onExit`, `update` and `draw` |
| `GameMaster` | Owns the components and the particle ring buffer, holds the states, exposes `active()`, `update()`, `draw()` |
| `RingBuffer<T>` | Generic fixed-capacity buffer used for the position trail and the particle pool |
| `Randomizer` | Seeded uniform random doubles over a range |

Each frame, `PlayState` handles a pause request, reads input, calls `Engine::updatePlayer`, spawns particles if a wall was hit, and advances live particles.

## Tuning

Game feel is controlled by a handful of constants. They are tuned by feel and still subject to change.

| Constant | Where | Value |
| --- | --- | --- |
| `maximum_input_momentum` | `engine.hpp` | 815 |
| `maximum_global_momentum` | `engine.hpp` | 1225 |
| `friction` | `engine.hpp` | 41 |
| `elasticity` | `engine.hpp` | 0.25 |
| `centripetal` (spin speed) | `engine.hpp` | 270 |
| `points::per_wall` | `style.hpp` | 4.25 |
| `points::decay_delay` | `style.hpp` | 1.15 s |
| Grade `A` / `S` thresholds | `style.hpp` | 1× / 2× `per_wall` |

## Requirements

- Windows
- [MinGW-w64](https://www.mingw-w64.org/) providing `g++` (C++20 support) and `make`
- [raylib](https://github.com/raysan5/raylib) **built from source** at `C:/raylib/raylib`, so that `libraylib.a` sits in `C:/raylib/raylib/src`

System libraries linked: `opengl32`, `gdi32`, `winmm`.

## Building

```bash
git clone https://github.com/HondroceaDragos/MoveAble.git
cd MoveAble
make
```

This produces `movable.exe` in the repo root.

| Target | Description |
| --- | --- |
| `make` / `make all` | Build `movable.exe` |
| `make run` | Build (if needed) and launch the game |
| `make clean` | Delete `movable.exe` |

The Makefile compiles `main.cpp` together with every `.cpp` under `src/` (up to one subfolder deep), using `-O3 -Wall -std=c++20`.

### Using a different raylib location

The raylib paths are set at the top of the Makefile; edit them if yours differs:

```make
INCLUDES = -I C:/raylib/raylib/src
LDFLAGS  = -L C:/raylib/raylib/src
```

## Running

Run `make run`, or launch `movable.exe` directly from the repo root. Keep it there: the sprites and font are loaded with relative paths.