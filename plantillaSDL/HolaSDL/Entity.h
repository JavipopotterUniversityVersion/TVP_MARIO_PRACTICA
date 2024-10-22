#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include "Game.h"

class Entity
{
	private:
		Point2D<int> position;
		int direction;
		Texture* texture;
		Game* game;
		int vidas;

	public:
		Entity(Game* game, int x, int y);
		void render();
		virtual void update();
		virtual void hit();
};

