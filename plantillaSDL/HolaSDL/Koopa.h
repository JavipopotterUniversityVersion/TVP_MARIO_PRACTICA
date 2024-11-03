#pragma once
#include "Vector2D.h"
#include "Texture.h"
class Game;

class Koopa 
{
	private:
		Vector2D<int> position;
		int direction = 0;
		Texture* texture;
		Game* game;

	public:
		Koopa(Game* game, int x, int y);
		void render();
		void handleEvent(SDL_Event& evento);
		void update();
		void hit();
};