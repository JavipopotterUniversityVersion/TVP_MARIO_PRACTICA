#include "SceneObject.h"
#include "Texture.h"
#include "SDL.h"
#include "Game.h"

SceneObject::SceneObject(Game* game, int x, int y)
{
	this->game = game;
	position.Set(x, y);
}

SDL_Rect SceneObject::getCollisionRect()
{
	SDL_Rect rect;

	Vector2D<float> realPos = position;
	realPos.setY(realPos.getY());
	Vector2D<float> screenPosition = Vector2D<float>((position.getX() * Game::TILE_SIDE) - game->GetMapOffset(), position.getY() * Game::TILE_SIDE);

	rect.x = screenPosition.getX();
	rect.y = screenPosition.getY();
	rect.w = Game::TILE_SIDE;
	rect.h = Game::TILE_SIDE;

	return rect;
}

void SceneObject::render()
{
	currentFrame++;

	if (currentFrame > frameRange.getY())
	{
		currentFrame = frameRange.getX();
	}

	SDL_Rect rect = getCollisionRect();
	texture->renderFrame(rect, 0, currentFrame);
}

Collision SceneObject::tryToMove(Vector2D<float> direction, Collision::Target target)
{
	SDL_Rect rect = getCollisionRect();

	rect.x += direction.getX();
	rect.y += direction.getY();

	Collision col = game->checkCollision(rect, target);

	return col;
}

void SceneObject::update()
{
	position.Set(position.getX() + velocity.getX(), position.getY() + velocity.getY());
}