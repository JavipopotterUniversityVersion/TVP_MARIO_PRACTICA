#pragma once
#include "Vector2D.h"
#include "Texture.h"
class Game;

class Goomba 
{
	private:
		Vector2D<float> position;
		static constexpr float SPEED = 0.05f;
		static constexpr float GRAVITY = 1.0f;
		int direction = -1;
		int lastDirection = 1;
		Texture* texture;
		Game* game;
		SDL_Rect* rect;
		void updateRect();

	public:
		Goomba(Game* game, int x, int y);
		void render();
		void update();
		void hit();
		SDL_Rect getRect() { return *rect; }
};