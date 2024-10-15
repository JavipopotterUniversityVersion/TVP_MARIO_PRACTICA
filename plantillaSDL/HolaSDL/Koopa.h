#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include "Game.h"

class Koopa
{
	Point2D<int> position;
	int direction;
	Texture* texture;
	Game* game;

	Koopa(Game* game, int x, int y);

	void render();
	void update();
	void hit();
};

