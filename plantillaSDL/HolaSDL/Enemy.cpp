#include "Enemy.h"
#include "Collision.h"
#include "Game.h"

void Enemy::update()
{
	// Acelra la velocidad con la gravedad
	if (velocity.getY() < SPEED_LIMIT)
		velocity += {0, SDL_App::GRAVITY};

	// Velocidad en este ciclo (no siempre avanza lateralmente)
	Vector2D<float> realSpeed = velocity;

	if (moveDelay-- == 0)
		moveDelay = MOVE_PERIOD;
	else
		realSpeed.setX(0);

	// Intenta moverse
	Collision collision = tryToMove(realSpeed, Collision::PLAYER);

	// Si toca un objeto en horizontal cambia de dirección
	if (collision.horizontal)
		velocity.setX(-velocity.getX());

	// Si toca un objeto en vertical anula la velocidad (para que no se acumule la gravedad)
	if (collision.vertical)
		velocity.setY(0);

	// SceneObject::update(); // si hiciera falta
}

Collision Enemy::hit(const SDL_Rect& region, Collision::Target target)
{
	Collision collision;
	if (target == Collision::ENEMIES)
	{
		if (region.y < getCollisionRect().y)
		{
			delete this;
			collision.result = Collision::DAMAGE;
		}
	}
	return collision;
}