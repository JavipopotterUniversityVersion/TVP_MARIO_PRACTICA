#include "bullet.h"
#include "PlayState.h"

Bullet::Bullet(PlayState* game, int x, int y, Vector2D<float> direction) : SceneObject(game, x, y)
{
	velocity = direction * SPEED;
	_width = _height = 8;
	texture = game->getApp()->getTexture(SDL_App::BULLET);
}

Collision Bullet::hit(const SDL_Rect& region, Collision::Target target)
{
	return Collision{};
}

void Bullet::update()
{
	position += velocity;

	SDL_Rect rect = getCollisionRect();
	Collision result = playState->checkCollision(rect, Collision::Bullet);
	if (result.result != Collision::NONE) delete this;

	SceneObject::update();
}