#pragma once
#include "Vector2D.h"
#include "Texture.h"
class SDL_App;

class Koopa 
{
	private:
		Vector2D<int> position;
		int direction = 0;
		Texture* texture;
		SDL_App* game;

	public:
		Koopa(SDL_App* game, int x, int y);
		void render();
		void handleEvent(SDL_Event& evento);
		void update();
		void hit();
};