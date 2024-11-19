#pragma once
//class Entity;
#include "Vector2D.h"
#include "Texture.h"
#include "SceneObject.h"
class Game;

class Player : public SceneObject
{
	private:
		static constexpr float JUMP_TIME = 0.5f;
		static constexpr float SPEED = 0.35f;
		static constexpr float JUMP_FORCE = 1;
		static constexpr float INMUNE_TIME = 1.5f;

		Vector2D<float> initialPosition;
		int lastDirection = 1;
		int direction = 0;
		Texture* texture;
		bool canJump = false;
		float jumpTimer = JUMP_TIME;
		float inmuneTimer = INMUNE_TIME;
		Game* game;
		int vidas;
		SDL_Rect* rect;
		bool flipped = false;
		int currentFrame = 0;
		Vector2D<int> frameRange;
		bool superMario = false;

		void SetFrameRange(int x, int y) { frameRange.Set(x, y); }

	public:
		Player(Game* game, int x, int y, int vidas);
		void render();
		void handleEvent(SDL_Event& evento);

		void update();
		void hit();
		void defeatedEnemy();

		int GetRectXPosition() { return position.getX() * 32; };
		void SetDirection(int dir) { direction = dir; }

		void updateRect();
		SDL_Rect getRect() { return *rect; }

		void goSuperMario();
};