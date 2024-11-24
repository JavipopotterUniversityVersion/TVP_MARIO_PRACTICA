#include "Goomba.h"
#include "Game.h"
#include "Collision.h"
#include "Vector2D.h"

void Goomba::updateRect()
{
	Vector2D<float> screenPosition = game->WorldToScreen(position);
	rect->x = screenPosition.getX();
	rect->y = screenPosition.getY();
}

void Goomba::render()
{
	if (!active) return;

	currentFrame += 1;
	if (currentFrame > frameRange.getY() || currentFrame < frameRange.getX()) currentFrame = frameRange.getX();
	texture->renderFrame(*rect, 0, currentFrame);
}

Goomba::Goomba(Game* game, int x, int y, bool isKoopa = false) : game(game), texture(game->getTexture(isKoopa ? Game::KOOPA : Game::GOOMBA))
{
	frameRange.Set(0, 1);
	position.Set(x, y - 1);
	rect = new SDL_Rect();
	rect->w = Game::TILE_SIZE;
	rect->h = Game::TILE_SIZE;
	updateRect();
}

void Goomba::hit()
{
	//cout << "Goomba hit" << endl;
	active = false;
}