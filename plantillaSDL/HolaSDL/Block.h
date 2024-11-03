#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include "Game.h"

enum BlockType { LADRILLO, SORPRESA, VACIO, OCULTO };
enum BlockAction { POTENCIADOR, MONEDA };

class Block
{
	private:
		Vector2D<int> position;
		BlockType type;
		BlockAction action;
		Game* game;
		Texture* texture;

	public:
		Block(Game* game, int x, int y, BlockType type, BlockAction action = MONEDA) :
			game(game), texture(game->getTexture(Game::BLOCKS)), type(type), action(action) {};
		void render();
		virtual void update();
		virtual void hit();
};