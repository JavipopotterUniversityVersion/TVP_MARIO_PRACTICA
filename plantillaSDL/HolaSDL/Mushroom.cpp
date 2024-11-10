#include "Mushroom.h"
#include "Game.h"
#include "Texture.h"
#include "Collision.h"
#include "Vector2D.h"

void Mushroom::updateRect()
{
	Vector2D<float> screenPosition = game->WorldToScreen(position);
	rect->x = screenPosition.getX();
	rect->y = screenPosition.getY();
}

void Mushroom::render()
{
	if (!active) return;

	texture->renderFrame(*rect, 0, 0);
}

void Mushroom::update()
{
	if (!active) return;

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

Mushroom::Mushroom(int x, int y, Game* game) : game(game), texture(game->getTexture(Game::MUSHROOM))
{
	position.Set(x, y - 1);
	rect = new SDL_Rect();
	rect->w = Game::TILE_SIZE;
	rect->h = Game::TILE_SIZE;
	updateRect();
}

void Mushroom::place(int x, int y)
{
	position.Set(x, y - 1);
	active = true;
}

void Mushroom::hit()
{
	active = false;
}