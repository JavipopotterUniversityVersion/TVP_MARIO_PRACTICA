#pragma once
//class Entity;
#include "Vector2D.h"
#include "Texture.h"
class Game;

class Player /*: public Entity*/
{
	/*private:
		int direction;

		bool superMario = false;
		int vidas = 3;

	public:
		Player(Game* game, int x, int y) : Entity(game, x, y, 3, game->getTexture(Game::MARIO)) {}
		void handleEvent();*/

	private:
		static constexpr float JUMP_TIME = 0.5f;
		static constexpr float SPEED = 0.35f;
		static constexpr float JUMP_FORCE = 1;
		Vector2D<float> position;
		int lastDirection = 1;
		int direction = 0;
		Texture* texture;
		bool canJump = true;
		float jumpTimer = JUMP_TIME;
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