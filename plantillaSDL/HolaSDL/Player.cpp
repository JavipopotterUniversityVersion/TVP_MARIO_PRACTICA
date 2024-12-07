#include "Player.h"
#include "PlayState.h"
#include "Vector2D.h"
#include "Collision.h"
#include "PauseState.h"
#include "AnimationState.h"

Player::Player(PlayState* game, int x, int y, int vidas) : SceneObject(game, x, y), vidas(vidas)
{
	this->texture = game->getApp()->getTexture(SDL_App::MARIO);
	initialPos.Set(x, y);
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
				case SDLK_ESCAPE:
					game->getApp()->pushState(new PauseState(game->getApp()));
					break;
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
	texture = playState->getApp()->getTexture(SDL_App::SUPERMARIO);
}

void Player::update()
{
	// Acelra la velocidad con la gravedad
	if (velocity.getY() < SPEED_LIMIT)
		velocity += {0, SDL_App::GRAVITY};

	// Velocidad en este ciclo (no siempre avanza lateralmente)
	Vector2D<float> realSpeed = velocity;

	if (moveDelay-- == 0)
		moveDelay = MOVE_PERIOD;
	//else
		//realSpeed.setX(0);

	// Intenta moverse
	Collision collision = tryToMove(realSpeed, Collision::ENEMIES);

	// Si toca un objeto en horizontal cambia de direcci�n
	if (collision.horizontal)
		velocity.setX(-velocity.getX());

	// Si toca un objeto en vertical anula la velocidad (para que no se acumule la gravedad)
	if (collision.vertical)
	{
		canJump = true;
		velocity.setY(0);
	}

	if (position.getY() >= SDL_App::WIN_HEIGHT)
	{
		if (superMario) getDmg();
		getDmg();
	}

	// SceneObject::update(); // si hiciera falta
}

Collision Player::hit(const SDL_Rect& region, Collision::Target target)
{
	Collision col;
	SDL_Rect rect = getCollisionRect();

	if (SDL_HasIntersection(&region, &rect) && target == Collision::PLAYER)
	{
		if (region.y >= getCollisionRect().y)
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
		texture = game->getApp()->getTexture(SDL_App::MARIO);
	}
	else
	{
		vidas--;
		velocity.Set(0, -JUMP_FORCE);
		currentFrame = 1;
		game->getApp()->pushState(new AnimationState(playState, [this]() {
			return deathAnimation();
			}));
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
		rect.y -= SDL_App::TILE_SIDE;
	}
	return rect;
}

SDL_Rect Player::getCollisionRect() const
{
	SDL_Rect rect = SceneObject::getCollisionRect();
	if (superMario)
	{
		rect.h *= 2;
		rect.y -= SDL_App::TILE_SIDE;
	}
	return rect;
}

bool Player::deathAnimation()
{
	position += velocity;
	if (velocity.getY() < SPEED_LIMIT) velocity += {0, SDL_App::GRAVITY};
	return position.getY() < SDL_App::WIN_HEIGHT;
}