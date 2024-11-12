#include "Player.h"
#include "Game.h"
#include "Vector2D.h"
#include "Collision.h"

void Player::updateRect()
{
	Vector2D<float> screenPosition = game->WorldToScreen(position);
	rect->x = screenPosition.getX();
	rect->y = screenPosition.getY();
	if (superMario) rect->y -= Game::TILE_SIZE;
}

void Player::render()
{
	SDL_RendererFlip flip;
	flip = flipped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

	currentFrame += 1;
	if (currentFrame > frameRange.getY() || currentFrame < frameRange.getX()) currentFrame = frameRange.getX();

	texture->renderFrame(*rect, 0, currentFrame, flip);
}

void Player::update()
{
	SDL_Rect futureRect;

	if (rect->y > Game::WIN_HEIGHT)
	{
		if (superMario) hit();
		hit();
	}

	if (inmuneTimer < INMUNE_TIME) inmuneTimer += 0.1;

	if (jumpTimer < JUMP_TIME)
	{
		jumpTimer += 0.1;
		int newPos = position.getY() - Player::JUMP_FORCE;
		position.Set(position.getX(), newPos);
		futureRect.y = rect->y - Player::JUMP_FORCE;
		frameRange.Set(6, 6);
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

	if (game->checkCollision(futureRect, Collision::MARIO, superMario))
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

	if (game->checkCollision(futureRect, Collision::MARIO, superMario))
	{
		position.Set(position.getX() - (lastDirection * SPEED), position.getY());
	}

	if (direction != 0)
	{
		if (lastDirection != direction)
		{
			flipped = !flipped;
		}

		if(canJump) frameRange.Set(2, 4);
		lastDirection = direction;
	}
	else
	{
		if(canJump) frameRange.Set(0, 0);
	}

	updateRect();
}

Player::Player(Game* game, int x, int y, int vidas) : game(game), texture(game->getTexture(Game::MARIO)), vidas(vidas)
{
	position.Set(x, y);
	initialPosition.Set(x, y);
	rect = new SDL_Rect();
	rect->w = Game::TILE_SIZE;
	rect->h = Game::TILE_SIZE;
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

void Player::goSuperMario()
{
	superMario = true;
	rect->h = Game::TILE_SIZE * 2;
	texture = game->getTexture(Game::SUPERMARIO);
}

void Player::hit()
{
	if (inmuneTimer >= INMUNE_TIME)
	{
		inmuneTimer = 0;

		if (superMario)
		{
			superMario = false;
			rect->h = Game::TILE_SIZE;
			texture = game->getTexture(Game::MARIO);
		}
		else
		{
			vidas--;
			if (vidas <= 0) game->endgame();
			game->reset();
			position.Set(initialPosition.getX(), initialPosition.getY());
		}
	}
}

void Player::defeatedEnemy()
{
	jumpTimer = JUMP_TIME / 2;
}