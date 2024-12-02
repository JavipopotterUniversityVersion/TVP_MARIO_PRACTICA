#include "Mushroom.h"
#include "PlayState.h"
#include "Texture.h"
#include "Collision.h"
#include "Vector2D.h"

void Mushroom::triggerAction()
{
	//game->goSuperMario();
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
	{
		velocity.setY(velocity.getY() + SDL_App::GRAVITY);
	}
	Vector2D<float> realSpeed = velocity;
	realSpeed.setY(realSpeed.getY() + 1);

	Collision collision = tryToMove(realSpeed, Collision::NO);

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
	collision = tryToMove(realSpeed, Collision::NO);

	// Si toca un objeto en horizontal cambia de dirección
	if (collision.horizontal)
	{
		velocity.setX(-velocity.getX());
	}

	SceneObject::update();
}