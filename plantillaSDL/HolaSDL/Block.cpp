#include "Block.h"
#include "Game.h"

Block::Block(Game* game, int x, int y, BlockType type, BlockAction action = MONEDA) :
	game(game), texture(game->getTexture(Game::BLOCKS)), type(type), action(action)
{
	position.Set(x, y);
}

void Block::render()
{
	SDL_Rect rect;
	rect.w = 32;
	rect.h = 32;
	rect.x = (position.getX() * Game::TILE_SIZE) - game->GetMapOffset();
	rect.y = position.getY() * Game::TILE_SIZE;
	texture->renderFrame(rect, 0, 0);
	//LETS FAKIN GOOOOO
}