#include "Player.h"
#include "Game.h"
#include "Vector2D.h"
#include "Collision.h"

Player::Player(Game* game, int x, int y, int vidas) : vidas(vidas)
{
	this->game = game;
	this->texture = game->getTexture(Game::MARIO);

	position.Set(x, y);
	initialPosition.Set(x, y);
}

void Player::handleEvent(SDL_Event& evento)
{
		if (evento.type == SDL_KEYDOWN)
		{
			switch (evento.type)
			{
			case SDL_KEYDOWN:
				switch (evento.key.keysym.sym)
				{
				case SDLK_LEFT:
					velocity.setX(-1);
					break;
				case SDLK_RIGHT:
					velocity.setX(1);
					break;
				case SDLK_UP:
					if (canJump)
					{
						canJump = false;
						jumpTimer = 0;
					}
					break;
				default:
					break;
				}
			}
		}
		else if (evento.type == SDL_KEYUP)
		{
			switch (evento.key.keysym.sym)
			{
			case SDLK_LEFT:
				velocity.setX(-SPEED);
				break;
			case SDLK_RIGHT:
				velocity.setX(SPEED);
				break;
			case SDLK_UP:
				jumpTimer = Player::JUMP_TIME;
				break;
			default:
				break;
			}
		}
}

void Player::goSuperMario()
{
	superMario = true;
	texture = game->getTexture(Game::SUPERMARIO);
}

void Player::update()
{
	// Acelra la velocidad con la gravedad
	if (velocity.getY() < SPEED_LIMIT)
		velocity += {0, Game::GRAVITY};

	// Velocidad en este ciclo (no siempre avanza lateralmente)
	Vector2D<float> realSpeed = velocity;

	if (moveDelay-- == 0)
		moveDelay = MOVE_PERIOD;
	else
		realSpeed.setX(0);

	// Intenta moverse
	Collision collision = tryToMove(realSpeed, Collision::ENEMIES);

	// Si toca un objeto en horizontal cambia de dirección
	if (collision.horizontal)
		velocity.setX(-velocity.getX());

	// Si toca un objeto en vertical anula la velocidad (para que no se acumule la gravedad)
	if (collision.vertical)
		velocity.setY(0);

	SceneObject::update();
}

Collision Player::hit(SDL_Rect rect, Collision::Target target)
{
	Collision col;

	if (target == Collision::PLAYER)
	{
		if (getCollisionRect().y < rect.y) col.result = Collision::DAMAGE;
	}

	return col;
}