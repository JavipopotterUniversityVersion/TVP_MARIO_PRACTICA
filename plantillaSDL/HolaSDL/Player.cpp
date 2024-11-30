#include "Player.h"
#include "Game.h"
#include "Vector2D.h"
#include "Collision.h"

Player::Player(Game* game, int x, int y, int vidas) : SceneObject(game, x, y), vidas(vidas)
{
	this->texture = game->getTexture(Game::MARIO);
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
					velocity.setX(-SPEED);
					frameRange.Set(2, 4);
					break;
				case SDLK_RIGHT:
					velocity.setX(SPEED);
					frameRange.Set(2, 4);
					break;
				case SDLK_UP:
					if (canJump)
					{
						canJump = false;
						frameRange.Set(6,6);
						jumpTimer = 0;
						velocity.setY(-JUMP_FORCE);
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
				velocity.setX(0);
				frameRange.Set(0, 0);
				break;
			case SDLK_RIGHT:
				velocity.setX(0);
				frameRange.Set(0, 0);
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
	{
		velocity.setY(velocity.getY() + Game::GRAVITY);
	}
	Vector2D<float> realSpeed = velocity;
	realSpeed.setY(realSpeed.getY() + 1);

	Collision collision = tryToMove(realSpeed, Collision::ENEMIES);
	if (collision.result == Collision::DAMAGE) velocity.setY(-JUMP_FORCE);

	// Si toca un objeto en vertical anula la velocidad (para que no se acumule la gravedad)
	if (collision.vertical)
	{
		if(collision.vertical > position.getY() - 0.5f) position.setY(collision.vertical - 1);
		else position.setY(collision.vertical + 1);

		velocity.setY(0);
		if (canJump == false)
		{
			canJump = true;
			if(velocity.getX() == 0) frameRange.Set(0,0);
			else  frameRange.Set(2, 4);
		}
	}

	if (moveDelay-- == 0)
		moveDelay = MOVE_PERIOD;
	else
		realSpeed.setX(0);

	realSpeed = velocity;

	// Intenta moverse
	collision = tryToMove(realSpeed, Collision::ENEMIES);

	// Si toca un objeto en horizontal cambia de dirección
	if (collision.horizontal)
	{
		velocity.setX(0);
	}

	if (position.getY() > Game::WIN_HEIGHT / Game::TILE_SIDE)
	{
		if (superMario) getDmg();
		getDmg();
	}

	SceneObject::update();
}

Collision Player::hit(const SDL_Rect& region, Collision::Target target)
{
	Collision col;

	if (target == Collision::PLAYER)
	{
		if (region.y <= getCollisionRect().y)
		{
			getDmg();
		}
	}

	return col;
}

void Player::getDmg()
{
	if (superMario)
	{
		superMario = false;
		texture = game->getTexture(Game::MARIO);
	}
	else
	{
		vidas--;
		game->resetFlag();
	}
}

SceneObject* Player::clone()
{
	return new Player(*this);
}

SDL_Rect Player::getRenderRect() const
{
	SDL_Rect rect = SceneObject::getRenderRect();
	if (superMario)
	{
		rect.h *= 2;
		rect.y -= Game::TILE_SIDE;
	}
	return rect;
}

SDL_Rect Player::getCollisionRect() const
{
	SDL_Rect rect = SceneObject::getCollisionRect();
	if (superMario)
	{
		rect.h *= 2;
		rect.y -= Game::TILE_SIDE;
	}
	return rect;
}