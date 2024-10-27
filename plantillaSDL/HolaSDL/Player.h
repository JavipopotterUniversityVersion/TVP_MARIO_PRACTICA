#pragma once
class Entity;
class Texture;
class Game;

class Player : public Entity
{
	private:
		int direction;

		bool superMario = false;
		int vidas = 3;

	public:
		Player(Game* game, int x, int y) : Entity(game, x, y, 3, game->getTexture(Game::MARIO)) {}
		void handleEvent();
};