#include "Player.h"
#include "Game.h"
#include "Vector2D.h"

void Player::render()
{
	SDL_Rect rect;
	rect.w = 32;
	rect.h = 32;
	rect.x = 20;
	rect.y = 20;
	texture->renderFrame(rect, 0, 0);
	//LETS FAKIN GOOOOO
}

void Player::update()
{

}

void Player::hit()
{

}

Player::Player(Game* game, int x, int y) : texture(game->getTexture(Game::MARIO))
{
	direction = 0;
	vidas = 3;
	//position.Set(x, y);
}