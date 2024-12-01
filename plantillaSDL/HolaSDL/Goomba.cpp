#include "Goomba.h"
#include "Game.h"
#include "Collision.h"
#include "Vector2D.h"

Goomba::Goomba(SDL_App* game, int x, int y, bool isKoopa) : Enemy(game, x, y), isKoopa(isKoopa)
{
	texture = isKoopa ? game->getTexture(SDL_App::KOOPA) : game->getTexture(SDL_App::GOOMBA);
	velocity.setX(-0.1); 
}

SceneObject* Goomba::clone()
{
	return new Goomba(*this);
}