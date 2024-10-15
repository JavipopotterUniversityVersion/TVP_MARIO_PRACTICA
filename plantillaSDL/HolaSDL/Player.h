#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include "Game.h"

class Player
{
	Point2D<int> position;
	int direction;
	Texture* texture;
	Game* game;

	bool superMario = false;
	int vidas = 3;

	Player(Game* game, int x, int y);

	void render();
	void update();
	void hit();
};