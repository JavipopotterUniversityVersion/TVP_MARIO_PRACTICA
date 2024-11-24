#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include "Enemy.h"
class Game;

class Goomba : public Enemy
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
		bool active = true;
		int currentFrame = 0;
		Vector2D<int> frameRange;

	public:
		Goomba(Game* game, int x, int y, bool isKoopa);
		void render();
		void update();
		void hit();
		SDL_Rect getRect() { return *rect; }
		bool isActive() { return active; }
};