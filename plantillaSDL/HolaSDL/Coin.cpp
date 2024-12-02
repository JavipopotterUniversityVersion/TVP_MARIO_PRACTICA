#include "Coin.h"
#include "SDL_App.h"
#include "PlayState.h"

void Coin::triggerAction()
{
	playState->givePoints(200);
}

Coin::Coin(PlayState* game, int x, int y) : Pickable(game, x, y)
{
	frameRange.Set(0, 3);
	texture = game->getApp()->getTexture(SDL_App::COIN);
}

Coin::Coin(Coin& coin) : Coin(coin.playState, coin.position.getX(), coin.position.getY()) {}

SceneObject* Coin::clone()
{
	return new Coin(*this);
}