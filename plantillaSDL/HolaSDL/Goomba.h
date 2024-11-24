#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include "Enemy.h"
class Game;

class Goomba : public Enemy
{
	private:
		static constexpr float SPEED = 0.05f;
		bool active = true;
		int currentFrame = 0;
		Vector2D<int> frameRange;

	public:
		bool isActive() { return active; }
		Goomba(Game* game, int x, int y) : Enemy(game, x, y) { texture = game->getTexture(Game::GOOMBA); }
};