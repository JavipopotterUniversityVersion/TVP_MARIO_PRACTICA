#include "Coin.h"
#include "Game.h"

void Coin::triggerAction()
{
	game->givePoints(200);
}