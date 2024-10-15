#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include "Game.h"

enum BlockType { LADRILLO, SORPRESA, VACIO, OCULTO };
enum BlockAction { POTENCIADOR, MONEDA };

class Block
{
	Point2D<int> position;
	Texture* texture;
	Game* game;

	BlockType type;
	BlockAction action;

	void render();
	void update();
	void hit();
};