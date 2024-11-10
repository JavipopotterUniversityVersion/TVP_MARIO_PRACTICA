#include "Player.h"
#include "Game.h"
#include "Vector2D.h"
#include "Collision.h"

void Player::updateRect()
{
	Vector2D<float> screenPosition = game->WorldToScreen(position);
	rect->x = screenPosition.getX();
	rect->y = screenPosition.getY();
}

void Player::render()
{
	texture->renderFrame(*rect, 0, 0);
}

void Player::update()
{
	position.Set(position.getX(), position.getY());
	SDL_Rect futureRect;

	if (jumpTimer < JUMP_TIME)
	{
		jumpTimer += 0.1;
		int newPos = position.getY() - Player::JUMP_FORCE;
		position.Set(position.getX(), newPos);
		futureRect.y = rect->y - Player::JUMP_FORCE;
	}
	else
	{
		int newPos = position.getY() + Player::JUMP_FORCE;
		position.Set(position.getX(), newPos);
		futureRect.y = rect->y + Player::JUMP_FORCE;
	}

	futureRect.x = rect->x;
	futureRect.w = rect->w;
	futureRect.h = rect->h;

	if (game->checkCollision(futureRect, Collision::MARIO))
	{
		if (jumpTimer < JUMP_TIME)
		{
			jumpTimer = JUMP_TIME;
			position.Set(position.getX(), position.getY() + Player::JUMP_FORCE);
		}
		else
		{
			position.Set(position.getX(), position.getY() - Player::JUMP_FORCE);
			canJump = true;
		}
	}

	futureRect.y = rect->y;
	position.Set(position.getX() + (direction * SPEED), position.getY());
	futureRect.x = rect->x + (direction * SPEED);

	if (game->checkCollision(futureRect, Collision::MARIO))
	{
		position.Set(position.getX() - (lastDirection * SPEED), position.getY());
	}

	if (direction != 0) lastDirection = direction;
	updateRect();
}

Player::Player(Game* game, int x, int y, int vidas) : game(game), texture(game->getTexture(Game::MARIO)), vidas(vidas)
{
	position.Set(x, y);
	rect = new SDL_Rect();
	rect->w = 32;
	rect->h = 32;
	updateRect();
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
					Player::SetDirection(-1);
					break;
				case SDLK_RIGHT:
					SetDirection(1);
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
				Player::SetDirection(0);
				break;
			case SDLK_RIGHT:
				SetDirection(0);
				break;
			case SDLK_UP:
				jumpTimer = Player::JUMP_TIME;
				break;
			default:
				break;
			}
		}
}

void Player::hit()
{
	vidas--;
}