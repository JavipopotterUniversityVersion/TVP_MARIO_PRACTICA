#include "Player.h"
#include "PlayState.h"
#include "Vector2D.h"
#include "Collision.h"
#include "PauseState.h"
#include "AnimationState.h"
#include "EndState.h"
#include "Shotgun.h"

Player::Player(PlayState* game, int x, int y, int vidas) : SceneObject(game, x, y), vidas(vidas)
{
	this->texture = game->getApp()->getTexture(SDL_App::MARIO);
	initialPos.Set(x, y);
}

void Player::handleEvent(SDL_Event& evento)
{
		if(evento.type == SDL_MOUSEBUTTONDOWN) if (_currentWeapon != nullptr) _currentWeapon->Use();
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
				case SDLK_a:
					velocity.setX(-SPEED);
					frameRange.Set(2, 4);
					break;
				case SDLK_d:
					velocity.setX(SPEED);
					frameRange.Set(2, 4);
					break;
				case SDLK_w:
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
			case SDLK_a:
				velocity.setX(0);
				frameRange.Set(0, 0);
				break;
			case SDLK_d:
				velocity.setX(0);
				frameRange.Set(0, 0);
				break;
			case SDLK_w:
				velocity.setY(0);
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
	if(collision.result == Collision::DAMAGE) velocity.setY(-JUMP_FORCE);

	// Si toca un objeto en vertical anula la velocidad (para que no se acumule la gravedad)
	if (collision.vertical)
	{
		canJump = true;
		velocity.setY(0);
		velocity.getX() != 0 ? frameRange.Set(2, 4) : frameRange.Set(0, 0);
	}

	if (position.getY() >= SDL_App::WIN_HEIGHT)
	{
		if (superMario) getDmg();
		getDmg();
	}

	if (inmuneTimer > 0)
	{
		inmuneTimer -= 0.1f;
		_visible = !_visible;
		if (inmuneTimer <= 0) _visible = true;
	}

	if (_currentWeapon != nullptr)
	{
		int x;
		int y;

		SDL_GetMouseState(&x, &y);
		Vector2D<float> direction{ Vector2D<float>(x, y) - Vector2D<float>(position.getX() - playState->getMapOffset(), position.getY())};

		double rot = direction.getY() / direction.getX();
		rot = atan(rot);

		rot *= 180;
		rot /= M_PI;

		if (direction.getX() < 0) _currentWeapon->setFlip(SDL_FLIP_HORIZONTAL);
		else _currentWeapon->setFlip(SDL_FLIP_NONE);

		_currentWeapon->setRotation(rot);
	}

	SceneObject::update(); // si hiciera falta
}

void Player::render() const
{
	if (isVisible())
	{
		SceneObject::render();
	}
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
	if (inmuneTimer > 0) return;

	if (superMario)
	{
		inmuneTimer = INMUNE_TIME;
		superMario = false;
		texture = game->getApp()->getTexture(SDL_App::MARIO);
	}
	else
	{
		vidas--;
		velocity.Set(0, -JUMP_FORCE);
		currentFrame = 1;

		if (vidas <= 0)
		{
			game->getApp()->replaceState(new EndState(game->getApp()));
		}
		else
		{
			game->getApp()->pushState(new AnimationState(playState, [this]() {
				return deathAnimation();
				}));
		}
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