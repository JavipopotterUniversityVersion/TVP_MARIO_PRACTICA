#include "Lift.h"
#include "Game.h"

void Lift::update()
{
	position.setY(position.getY() + speed);

	if (position.getY() < 0) position.setY(Game::WIN_HEIGHT / Game::TILE_SIDE);
	else if (position.getY() > Game::WIN_HEIGHT / Game::TILE_SIDE) position.setY(0);
}

Collision Lift::hit(SDL_Rect rect, Collision::Target target)
{

	SDL_Rect intersection;
	SDL_Rect thisRect = getCollisionRect();
	SDL_IntersectRect(&rect, &thisRect, &intersection);

	Collision collision{ Collision::OBSTACLE, intersection.w };
	collision.vertical = position.getY();

	return collision;
}

SceneObject* Lift::clone()
{
	return new Lift(game, position.getX(), position.getY(), velocity.getY() / speed);
}

Lift::Lift(Game* game, int x, int y, int direction) : SceneObject(game, x, y)
{
	texture = game->getTexture(Game::LIFT);
	velocity.setY(speed*direction);
}

void Lift::render()
{
	SDL_Rect rect = getRenderRect();
	rect.w *= 3;
	texture->renderFrame(rect, 0, 0);
}

SDL_Rect Lift::getCollisionRect()
{
	SDL_Rect rect = SceneObject::getCollisionRect();
	rect.w *= 3;
	return rect;
}