#include "Lift.h"
#include "PlayState.h"
#include "SDL_App.h"

void Lift::update()
{
	position.setY(position.getY() + speed);

	if (position.getY() < 0) position.setY(SDL_App::WIN_HEIGHT / SDL_App::TILE_SIDE);
	else if (position.getY() > SDL_App::WIN_HEIGHT / SDL_App::TILE_SIDE) position.setY(0);
}

Collision Lift::hit(const SDL_Rect& region, Collision::Target target)
{
	SDL_Rect intersection;
	SDL_Rect ownRect = getCollisionRect();

	if (SDL_IntersectRect(&ownRect, &region, &intersection))
	{
		Collision collision{ Collision::OBSTACLE, intersection.w, intersection.h };
		return collision;
	}

	return Collision{};
}

SceneObject* Lift::clone()
{
	return new Lift(playState, position.getX(), position.getY(), velocity.getY() / speed);
}

Lift::Lift(PlayState* game, int x, int y, int direction) : SceneObject(game, x, y)
{
	texture = game->getApp()->getTexture(SDL_App::LIFT);
	velocity.setY(speed*direction);
}

void Lift::render() const
{
	SDL_Rect rect = getRenderRect();
	rect.w *= 3;
	texture->renderFrame(rect, 0, 0);
}

SDL_Rect Lift::getCollisionRect() const
{
	SDL_Rect rect = SceneObject::getCollisionRect();
	rect.w *= 3;
	return rect;
}