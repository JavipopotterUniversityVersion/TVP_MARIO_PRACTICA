#pragma once
#include "Vector2D.h"
class Texture;
class Game;
#include "Entity.h"

class Player : public Entity
{
	private:
		int direction;

		bool superMario = false;
		int vidas = 3;

	public:
		Player(Game* game, int x, int y) : Entity(game, x, y) {}
		void handleEvent();
};