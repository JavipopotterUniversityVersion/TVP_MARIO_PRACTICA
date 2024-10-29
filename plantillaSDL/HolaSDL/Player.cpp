#include "Player.h"
#include "Game.h"
#include "Vector2D.h"

void Player::render()
{
	SDL_Rect rect;
	rect.w = 32;
	rect.h = 32;
	rect.x = position.getX() - game->GetMapOffset();
	rect.y = position.getY();
	texture->renderFrame(rect, 0, 0);
	//LETS FAKIN GOOOOO
}

void Player::update()
{
	position.Set(position.getX() + direction * SPEED, position.getY());
	
}

void Player::hit()
{

}

Player::Player(Game* game, int x, int y) : game(game), texture(game->getTexture(Game::MARIO))
{
	vidas = 3;
	position.Set(x, y);
}

//JODeEEEEEeEEEEEEeeeeeeEEeEEeEeeeer
void Player::handleEvent()
{
	SDL_Event evento;
	while (SDL_PollEvent(&evento)) {
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
				default:
					break;
				}
			}
		}
		else if (evento.type == SDL_KEYUP)
		{
			Player::SetDirection(0);
		}
	}
}