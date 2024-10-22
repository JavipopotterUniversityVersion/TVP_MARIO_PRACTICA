#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include "Game.h"
#include "Entity.h"

class Player : Entity
{
	private:
		Point2D<int> position;
		int direction;
		Texture* texture;
		Game* game;

		bool superMario = false;
		int vidas = 3;

	public:
		Player(Game* game, int x, int y);
		void handleEvent();

};