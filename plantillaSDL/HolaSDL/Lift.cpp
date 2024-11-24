#include "Lift.h"
#include "Game.h"

void Lift::update()
{
	position.setY(position.getY() + speed);

	if (position.getY() < 0) position.setY(game->WIN_HEIGHT * Game::TILE_SIDE);
	else if (position.getY() * Game::TILE_SIDE > game->WIN_HEIGHT) position.setY(0);
}