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
		Vector2D<int> position;
		int direction;
		Texture* texture;
		Game* game;
		int vidas;

	public:
		Player(Game* game, int x, int y);
		void render();
		void handleEvent(SDL_Event const& a);
		virtual void update();
		virtual void hit();
};