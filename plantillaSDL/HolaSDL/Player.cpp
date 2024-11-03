#include "Player.h"
#include "Game.h"
#include "Vector2D.h"

void Player::render()
{
	SDL_Rect rect;
	rect.w = 32;
	rect.h = 32;
	rect.x = (position.getX() * Game::TILE_SIZE) - game->GetMapOffset();
	rect.y = position.getY() * Game::TILE_SIZE;
	texture->renderFrame(rect, 0, 0);
	//LETS FAKIN GOOOOO
}

void Player::update()
{
	position.Set(position.getX() + direction * SPEED, position.getY());

	if (jumpTimer < JUMP_TIME)
	{
		jumpTimer += 0.1;
		int newPos = position.getY() - Player::JUMP_FORCE;
		position.Set(position.getX(), newPos);
	}
	else
	{
		int newPos = position.getY() + Player::JUMP_FORCE;

		if (position.getY() >= Game::FLOOR_HEIGHT)
		{
			canJump = true;
			newPos = Game::FLOOR_HEIGHT;
		}
		position.Set(position.getX(), newPos);
	}
}

void Player::hit()
{

}

Player::Player(Game* game, int x, int y, int vidas) : game(game), texture(game->getTexture(Game::MARIO)), vidas(vidas)
{
	position.Set(x, y);
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