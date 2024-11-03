#pragma once
#include "Texture.h"
#include "Vector2D.h"
class Game;

enum BlockType { LADRILLO, SORPRESA, VACIO, OCULTO };
enum BlockAction { POTENCIADOR, MONEDA };

class Block
{
	private:
		Vector2D<int> position;
		BlockType type;
		BlockAction action;
		Game* game;
		Texture* tecture;

	public:
		Block(Game* game, int x, int y, BlockType type, BlockAction action = MONEDA) :
			game(game), type(type), action(action) {};
};