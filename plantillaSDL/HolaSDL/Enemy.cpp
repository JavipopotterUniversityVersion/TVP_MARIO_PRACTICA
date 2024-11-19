#include "Enemy.h"
#include "Collision.h"
#include "Game.h"

void Enemy::update()
{
	// Acelra la velocidad con la gravedad
	if (speed.getY() < SPEED_LIMIT)
		speed += {0, Game::GRAVITY};

	// Velocidad en este ciclo (no siempre avanza lateralmente)
	Vector2D<float> realSpeed = speed;

	if (moveDelay-- == 0)
		moveDelay = MOVE_PERIOD;
	else
		realSpeed.setX(0);

	// Intenta moverse
	Collision collision = tryToMove(realSpeed, Collision::PLAYER);

	// Si toca un objeto en horizontal cambia de dirección
	if (collision.horizontal)
		speed.setX(-speed.getX());

	// Si toca un objeto en vertical anula la velocidad (para que no se acumule la gravedad)
	if (collision.vertical)
		speed.setY(0);

	SceneObject::update();
}