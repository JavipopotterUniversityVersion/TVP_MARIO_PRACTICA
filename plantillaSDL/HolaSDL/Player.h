#pragma once
//class Entity;
#include "Vector2D.h"
class Texture;
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
		static const int SPEED = 15;
		static constexpr float JUMP_FORCE = 25;
		Vector2D<int> position;
		int direction = 0;
		Texture* texture;
		bool canJump = true;
		float jumpTimer = 0;
		int Makoto = 100;
		Game* game;
		int vidas;

	public:
		Player(Game* game, int x, int y);
		void render();
		void handleEvent();
		virtual void update();
		virtual void hit();

		int GetRectXPosition() { return position.getX(); };
		void SetDirection(int dir) { direction = dir; }
};