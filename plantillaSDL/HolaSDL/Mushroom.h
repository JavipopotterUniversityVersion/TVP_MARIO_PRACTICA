#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include "SceneObject.h"
class Game;

class Mushroom : public SceneObject
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
		bool active = false;
	public:
		Mushroom(int x, int y, Game* game);
		~Mushroom();
		void render();
		void update();
		void hit();
		SDL_Rect getRect() { return *rect; }
		bool isActive() { return active; }
		void place(int x, int y);
};