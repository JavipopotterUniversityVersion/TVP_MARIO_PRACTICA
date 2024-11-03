#include "Goomba.h"
#include "Game.h"
#include "Collision.h"

Goomba::Goomba(Game* game, int x, int y) : game(game), texture(game->getTexture(Game::GOOMBA))
{
	position.Set(x, y);
}

void Goomba::render()
{
	SDL_Rect rect = getRect();
	texture->renderFrame(rect, 0, 0);
}

void Goomba::update()
{
	int newPos = position.getY() + 5;

	if (position.getY() >= Game::FLOOR_HEIGHT)
	{
		newPos = Game::FLOOR_HEIGHT;
	}
	position.Set(position.getX(), newPos);
}

SDL_Rect Goomba::getRect()
{
	SDL_Rect rect;
	rect.w = 32;
	rect.h = 32;
	rect.x = (position.getX() * Game::TILE_SIZE) - game->GetMapOffset();
	rect.y = position.getY() * Game::TILE_SIZE;
	return rect;
}

void Goomba::hit()
{

}