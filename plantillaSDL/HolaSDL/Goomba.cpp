#include "Goomba.h"
#include "Game.h"
#include "Collision.h"
#include "Vector2D.h"

Goomba::Goomba(Game* game, int x, int y, bool isKoopa) : Enemy(game, x, y), isKoopa(isKoopa)
{
	texture = isKoopa ? game->getTexture(Game::KOOPA) : game->getTexture(Game::GOOMBA);
	velocity.setX(-0.1); 
}

SceneObject* Goomba::clone()
{
	return new Goomba(*this);
}