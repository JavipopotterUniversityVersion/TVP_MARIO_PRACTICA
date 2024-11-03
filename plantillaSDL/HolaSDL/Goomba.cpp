#include "Goomba.h"
#include "Game.h"

Goomba::Goomba(Game* game, int x, int y) : game(game), texture(game->getTexture(Game::GOOMBA))
{
	position.Set(x, y);
	cout << endl << position.getX() << " " << position.getY();
}

void Goomba::render()
{
	SDL_Rect rect;
	rect.w = 32;
	rect.h = 32;
	rect.x = (position.getX() * Game::TILE_SIZE) - game->GetMapOffset();
	rect.y = position.getY() * Game::TILE_SIZE;
	texture->renderFrame(rect, 0, 0);
}

void Goomba::update()
{
	int newPos = position.getY() + 5;

	if (position.getY() >= 13)
	{
		cout << endl << position.getX() << " " << position.getY();
		newPos = 13;
	}
	position.Set(position.getX(), newPos);
}