#include "Player.h"
#include "Game.h"
#include "Vector2D.h"
#define event = SDL_Event;

void Player::render()
{
	SDL_Rect rect;
	rect.w = 32;
	rect.h = 32;
	rect.x = position.getX();
	rect.y = position.getY();
	texture->renderFrame(rect, 0, 0);
	//LETS FAKIN GOOOOO
}

void Player::update()
{
}

void Player::hit()
{

}

Player::Player(Game* game, int x, int y) : game(game), texture(game->getTexture(Game::MARIO))
{
	direction = 0;
	vidas = 3;
	position.Set(x, y);
}

//JODeEEEEEeEEEEEEeeeeeeEEeEEeEeeeer
void Player::handleEvent(SDL_Event const& a)
{
	switch (a.key.keysym.sym)
	{
	case SDLK_w: ;
		break;
	case SDLK_a: ;
		break;
	case SDLK_d: ;
		break;
	}
}