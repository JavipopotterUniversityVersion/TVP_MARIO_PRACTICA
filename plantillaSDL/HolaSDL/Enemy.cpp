#include "Enemy.h"
#include "Collision.h"
#include "Game.h"

void Enemy::update()
{
	// Acelra la velocidad con la gravedad
	if (velocity.getY() < SPEED_LIMIT)
		velocity.setY(velocity.getY() + Game::GRAVITY);

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

	SceneObject::update();
}

Collision Enemy::hit(SDL_Rect rect, Collision::Target target)
{
	Collision collision;
	return collision;
}