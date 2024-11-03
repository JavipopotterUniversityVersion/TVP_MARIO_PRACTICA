#pragma once
#include "Vector2D.h"
#include "Texture.h"
class Game;

class Goomba 
{
	private:
		Vector2D<int> position;
		int direction = 0;
		Texture* texture;
		Game* game;

	public:
		Goomba(Game* game, int x, int y);
		void render();
		void handleEvent(SDL_Event& evento);
		void update();
		void hit();

		SDL_Rect getRect();
};