#include "Mushroom.h"
#include "PlayState.h"
#include "Texture.h"
#include "Collision.h"
#include "Vector2D.h"

void Mushroom::triggerAction()
{
	playState->goSuperMario();
}

SceneObject* Mushroom::clone()
{
	return new Mushroom(playState, 0, 0);
}

Mushroom::Mushroom(PlayState* game, int x, int y) : Pickable(game, x, y)
{
	frameRange.Set(0, 0);
	texture = game->getApp()->getTexture(SDL_App::MUSHROOM);
	velocity.setX(SPEED);
}

void Mushroom::update()
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

	//SceneObject::update(); // si hiciera falta
}