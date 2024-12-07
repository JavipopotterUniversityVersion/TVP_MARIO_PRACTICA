#include "Goomba.h"
#include "Collision.h"
#include "Vector2D.h"
#include "PlayState.h"

Goomba::Goomba(PlayState* game, int x, int y, bool isKoopa) : Enemy(game, x, y), isKoopa(isKoopa)
{
	texture = isKoopa ? game->getApp()->getTexture(SDL_App::KOOPA) : game->getApp()->getTexture(SDL_App::GOOMBA);
	velocity.setX(-SPEED); 
}

SceneObject* Goomba::clone()
{
	return new Goomba(*this);
}