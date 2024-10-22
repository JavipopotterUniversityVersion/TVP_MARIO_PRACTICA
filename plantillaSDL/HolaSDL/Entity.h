#pragma once
#include "Vector2D.h"
#include "Texture.h"
class Game;

class Entity
{
	private:
		Vector2D<int> position;
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

