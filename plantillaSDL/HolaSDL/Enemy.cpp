#include "Enemy.h"
#include "Collision.h"
#include "SDL_App.h"

void Enemy::update()
{
	// Acelra la velocidad con la gravedad
	if (velocity.getY() < SPEED_LIMIT)
		velocity += {0, SDL_App::GRAVITY};

	// Velocidad en este ciclo (no siempre avanza lateralmente)
	Vector2D<float> realSpeed = velocity;

	if (moveDelay-- == 0)
		moveDelay = MOVE_PERIOD;
	//else
	//	realSpeed.setX(0);

	// Intenta moverse
	Collision collision = tryToMove(realSpeed, Collision::PLAYER);

	// Si toca un objeto en horizontal cambia de dirección
	if (collision.horizontal)
		velocity.setX(-velocity.getX());

	// Si toca un objeto en vertical anula la velocidad (para que no se acumule la gravedad)
	if (collision.vertical)
		velocity.setY(0);

	SceneObject::update(); // si hiciera falta
}

Collision Enemy::hit(const SDL_Rect& region, Collision::Target target)
{
	SDL_Rect rect = getCollisionRect();
	Collision collision;

	if (SDL_HasIntersection(&region, &rect))
	{
		if (target == Collision::ENEMIES && region.y < getCollisionRect().y)
		{
			delete this;
			collision.result = Collision::DAMAGE;
		}
		else if(target == Collision::Bullet) delete this;
	}

	return collision;
}