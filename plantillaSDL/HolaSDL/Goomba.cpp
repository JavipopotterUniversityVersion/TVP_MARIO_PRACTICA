#include "Goomba.h"
#include "Game.h"
#include "Collision.h"
#include "Vector2D.h"

Goomba::Goomba(Game* game, int x, int y) : Enemy(game, x, y) { texture = game->getTexture(Game::GOOMBA); }