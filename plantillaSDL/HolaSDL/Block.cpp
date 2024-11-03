#include "Block.h"
#include "Game.h"
#include "Collision.h"

Block::Block(Game* game, int x, int y, BlockType type, BlockAction action) :
	game(game), texture(game->getTexture(Game::BLOCKS)), type(type), action(action)
{
	position.Set(x, y);
}

void Block::render()
{
	SDL_Rect rect = getRect();
	texture->renderFrame(rect, 0, int(type));
	//LETS FAKIN GOOOOO
}

void Block::update()
{

}

SDL_Rect Block::getRect()
{
	SDL_Rect rect;
	rect.w = 32;
	rect.h = 32;
	rect.x = (position.getX() * Game::TILE_SIZE) - game->GetMapOffset();
	rect.y = position.getY() * Game::TILE_SIZE;
	return rect;
}

void Block::hit()
{

}