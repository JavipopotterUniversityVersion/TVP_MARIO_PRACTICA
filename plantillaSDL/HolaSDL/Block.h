#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include "Game.h"

enum BlockType { SORPRESA = 0, OCULTO, VACIO = 4, LADRILLO = 5};
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
		Block(Game* game, int x, int y, BlockType type, BlockAction action);
		void render();
		void update();
		void hit();
};