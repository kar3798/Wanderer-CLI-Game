# Wanderer — Roadmap & Task Sheet

Working agreement: one system at a time, fully understood before moving on (see commit history for the pattern — each commit is one system). This file is the running checklist across sessions.

## Phase 0 — Core foundation (done)
- [x] Entity/Item/Map/Tile architecture, Logger, cross-platform raw input
- [x] Turn-based command loop: WASD movement, directional attacks, inventory screen, message log
- [x] Entities carry an attack stat; enemy movement is obstacle- and occupancy-aware (no more walking into walls/other entities)
- [x] Procedural multi-room dungeon generation (`Map::generateDungeon`), replacing the fixed 10x10 room
- [x] Repo cleanup: stopped tracking the build binary and runtime log

## Phase 1 — Finish terminal gameplay (current focus)
Goal: a feature-complete terminal game — something actually fun to play start-to-finish in the console — before touching graphics or hardware.

- [x] Directional Shift+WASD attacks (previously ignored the direction and two keys were swapped)
- [x] Enemies attack the player when adjacent
- [x] HP display: player HP/ATK status line; enemy HP shown in hit messages
- [x] Lose condition: player death → GAME OVER screen
- [ ] Win condition: define what "winning" means (clear all enemies? reach stairs on the last floor?) — pairs well with multiple enemies/levels
- [ ] Intro/main menu: rules, how to play, a bit of lore — on the agenda, not yet scheduled
- [ ] Cleanup: `Player` redeclares its own `attack` (shadows `Entity::attack`) and `getHealth()` duplicates `getHP()`; `Enemy.cpp` has unused file-level `rng`/`dist` shadowed by the function-local ones
- [ ] Bump-to-attack: walking into an enemy attacks it (classic roguelike feel; frees Shift keys for later)
- [ ] Balance: potion costs 3 turns, so an adjacent enemy gets 3 hits (15 dmg) against a 20 HP heal — likely too punishing
- [ ] Give the Key a purpose: a door or locked chest tile/mechanic it actually unlocks (currently a placeholder with no effect).
- [ ] Loot drops: enemies drop something (item/currency) on death instead of just disappearing.
- [ ] Multiple enemy types: at least one more `Enemy`-derived type with different stats/behavior.
- [ ] Revisit item design: Sword is currently consumed on use like a potion — decide if weapons should instead be equipped and persist.
- [ ] Stretch: multiple levels/floors with stairs, now that dungeon generation exists per-level.

## Phase 2 — Smarter enemy AI
- [ ] Replace random-walk with real player-chasing behavior (simple pathfinding, e.g. BFS on the tile grid)
- [ ] This is the natural stepping stone toward the TinyML idea in Phase 5 — get a rule-based "smart" enemy working first, then decide what a learned model would actually improve

## Phase 3 — SDL2 rendering migration
- [ ] Separate rendering from game logic cleanly (today `GameLoop`/`Map` write straight to `std::cout`) so an SDL render layer can be swapped in without rewriting game rules
- [ ] Get a basic SDL2 window + tile-grid rendering working, replacing the terminal `render()`
- [ ] Port input handling from raw terminal `getCharInput()` to SDL events

## Phase 4 — Raspberry Pi 5 deployment
- [ ] Confirm build/toolchain on the Pi (cross-compile or build natively)
- [ ] Small screen output working via SDL on the Pi
- [ ] Custom keypad controller input wired up (replacing/supplementing keyboard)

## Phase 5 — TinyML enemy AI
- [ ] Define what the model actually decides (movement direction? attack vs. flee?) and what data trains it
- [ ] Integrate inference into `Enemy::update()` behind the same interface the Phase 2 pathfinding enemy uses, so it's a drop-in swap

## Phase 6 — Showcase polish
- [ ] README with screenshots/gif, build instructions, feature list
- [ ] Save/load
- [ ] Polish pass for demo-readiness

---
**Next concrete step:** pick one unchecked item from Phase 1 and we'll build it the same way as the last two systems — explained line by line, one PR-sized commit at a time.
