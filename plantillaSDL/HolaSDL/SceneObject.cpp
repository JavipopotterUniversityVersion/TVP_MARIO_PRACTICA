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

	Vector2D<float> screenPosition = game->WorldToScreen(position);
	rect.x = screenPosition.getX();
	rect.y = screenPosition.getY();

	return rect;
}

void SceneObject::render()
{
	currentFrame++;

	if (currentFrame > frameRange.getY())
	{
		currentFrame = frameRange.getX();
	}

	texture->renderFrame(getCollisionRect(), 0, currentFrame);
}

Collision SceneObject::tryToMove(Vector2D<float> direction, Collision::Target target)
{
	SDL_Rect rect = getCollisionRect();
	return game->checkCollision(rect, target);
}

void SceneObject::update()
{

}