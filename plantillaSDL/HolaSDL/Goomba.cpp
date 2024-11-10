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
	texture->renderFrame(*rect, 0, 0);
}

void Goomba::update()
{
	position.Set(position.getX(), position.getY());
	SDL_Rect futureRect;

	position.Set(position.getX(), position.getY() + GRAVITY);
	futureRect.y = rect->y + GRAVITY;

	futureRect.x = rect->x;
	futureRect.w = rect->w;
	futureRect.h = rect->h;

	if (game->checkCollision(futureRect, Collision::ENEMY))
	{
		position.Set(position.getX(), position.getY() - GRAVITY);
	}

	futureRect.y = rect->y;
	position.Set(position.getX() + (direction * SPEED), position.getY());
	futureRect.x = rect->x + (direction * SPEED);

	if (game->checkCollision(futureRect, Collision::ENEMY))
	{
		position.Set(position.getX() - (lastDirection * SPEED), position.getY());
		direction *= -1;
	}

	if (direction != 0) lastDirection = direction;
	updateRect();
}

Goomba::Goomba(Game* game, int x, int y) : game(game), texture(game->getTexture(Game::GOOMBA))
{
	position.Set(x, y);
	rect = new SDL_Rect();
	rect->w = Game::TILE_SIZE;
	rect->h = Game::TILE_SIZE;
	updateRect();
}

void Goomba::hit()
{
	
}