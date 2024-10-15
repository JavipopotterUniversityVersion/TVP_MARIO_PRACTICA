#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include "Game.h"

class Mushroom
{
	Point2D<int> position;
	int direction;
	Texture* texture;
	Game* game;

	Mushroom(Game* game, int x, int y);

	void render();
	void update();
	void hit();
};