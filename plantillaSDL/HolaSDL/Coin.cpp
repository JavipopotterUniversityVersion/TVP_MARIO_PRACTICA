#include "Coin.h"
#include "Game.h"

void Coin::triggerAction()
{
	game->givePoints(200);
}

Coin::Coin(SDL_App* game, int x, int y) : Pickable(game, x, y)
{
	frameRange.Set(0, 3);
	texture = game->getTexture(SDL_App::COIN);
}

Coin::Coin(Coin& coin) : Coin(coin.game, coin.position.getX(), coin.position.getY()) {}
SceneObject* Coin::clone()
{
	return new Coin(*this);
}