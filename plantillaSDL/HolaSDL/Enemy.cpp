#include "Enemy.h"
#include "Collision.h"
#include "Game.h"

void Enemy::update()
{
	// Acelra la velocidad con la gravedad
	if (velocity.getY() < SPEED_LIMIT)
	{
		velocity.setY(velocity.getY() + Game::GRAVITY);
	}
	Vector2D<float> realSpeed = velocity;
	realSpeed.setY(realSpeed.getY() + 1);

	Collision collision = tryToMove(realSpeed, Collision::PLAYER);

	// Si toca un objeto en vertical anula la velocidad (para que no se acumule la gravedad)
	if (collision.vertical)
	{
		if (collision.vertical > position.getY() - 0.5f) position.setY(collision.vertical - 1);
		else position.setY(collision.vertical + 1);

		velocity.setY(0);
	}

	if (moveDelay-- == 0)
		moveDelay = MOVE_PERIOD;
	else
		realSpeed.setX(0);

	realSpeed = velocity;

	// Intenta moverse
	collision = tryToMove(realSpeed, Collision::PLAYER);

	// Si toca un objeto en horizontal cambia de dirección
	if (collision.horizontal)
	{
		velocity.setX(-velocity.getX());
	}

	SceneObject::update();
}

Collision Enemy::hit(SDL_Rect rect, Collision::Target target)
{
	Collision collision;
	if (target == Collision::ENEMIES)
	{
		if (rect.y < getCollisionRect().y)
		{
			delete this;
			collision.result = Collision::DAMAGE;
		}
	}
	return collision;
}