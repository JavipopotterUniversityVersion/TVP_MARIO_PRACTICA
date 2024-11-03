#include "Player.h"
#include "Game.h"
#include "Vector2D.h"
#include "Collision.h"

SDL_Rect Player::getRect()
{
	SDL_Rect rect;
	rect.w = 32;
	rect.h = 32;
	rect.x = (position.getX() * Game::TILE_SIZE) - game->GetMapOffset();
	rect.y = position.getY() * Game::TILE_SIZE;
	return rect;
}

void Player::render()
{
	texture->renderFrame(getRect(), 0, 0);
	//LETS FAKIN GOOOOO
}

void Player::update()
{
	Vector2D<float> newPosition;
	newPosition.Set(position.getX(), position.getY());

	if (jumpTimer < JUMP_TIME)
	{
		jumpTimer += 0.1;
		int newPos = newPosition.getY() - Player::JUMP_FORCE;
		newPosition.Set(newPosition.getX(), newPos);
	}
	else
	{
		int newPos = newPosition.getY() + Player::JUMP_FORCE;

		if (newPosition.getY() >= Game::FLOOR_HEIGHT)
		{
			canJump = true;
			newPos = Game::FLOOR_HEIGHT;
		}
		newPosition.Set(newPosition.getX(), newPos);
	}

	SDL_Rect rect = getRect();
	Collision col = game->checkCollision(rect, true);

	if (col.damages) vidas--;
	if (col.collides == false)
	{
		position.Set(newPosition.getX(), newPosition.getY());
	}

	newPosition.Set(position.getX() + direction * SPEED, position.getY());
	position.Set(newPosition.getX(), newPosition.getY());
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