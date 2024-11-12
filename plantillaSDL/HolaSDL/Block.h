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
		int currentFrame = 0;
		Vector2D<int> frameRange;
		bool active = true;

	public:
		Block(Game* game, int x, int y, BlockType type, BlockAction action);
		void render();
		void hit(bool superMario);
		bool isActive() { return active; }

		SDL_Rect getRect();
};