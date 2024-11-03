#include "Block.h"

Block::Block(Game* game, int x, int y, BlockType type, BlockAction action = MONEDA) :
	game(game), type(type), action(action)
{
	position.Set(x, y);
}