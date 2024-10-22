#pragma once
#include "Entity.h"
#include "Game.h"

class Koopa : public Entity 
{
	public:
		Koopa(Game* game, int x, int y):Entity(game, x, y) {}
};