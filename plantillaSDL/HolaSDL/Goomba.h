#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include "Game.h"

class Goomba
{
	Point2D<int> position;
	int direction;
	Texture* texture;
	Game* game;

	Goomba(Game* game, int x, int y);

	void render();
	void update();
	void hit();
};

