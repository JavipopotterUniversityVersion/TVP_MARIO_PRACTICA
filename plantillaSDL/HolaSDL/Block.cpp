#include "Block.h"
#include "Game.h"
#include "Collision.h"

Block::Block(Game* game, int x, int y, BlockType type, BlockAction action) :
	game(game), texture(game->getTexture(Game::BLOCKS)), type(type), action(action)
{
	position.Set(x, y);
	if (type == SORPRESA) frameRange.Set(0, 3);
	else frameRange.Set(0, 0);
}

void Block::render()
{
	if (!active) return;

	SDL_Rect rect = getRect();

	currentFrame += 1;
	if (currentFrame > frameRange.getY() || currentFrame < frameRange.getX()) currentFrame = frameRange.getX();
	int frame = int(type) + currentFrame;

	if(type != OCULTO) texture->renderFrame(rect, 0, frame);
	//LETS FAKIN GOOOOO
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

void Block::hit(bool superMario)
{
	switch (type)
	{
		case SORPRESA:
		{
			if (action == MONEDA)
			{
				//game->addEntity(new Coin(game, position.getX(), position.getY()));
				type = VACIO;
			}
			else if (action == POTENCIADOR)
			{
				//game->addEntity(new Mushroom(game, position.getX(), position.getY()));
				game->placeMushroom(position.getX(), position.getY() - 1);
				type = VACIO;
			}
			frameRange.Set(0, 0);
		}
			break;
		case OCULTO:
			type = VACIO;
			break;
		case LADRILLO:
			if(superMario) active = false;
			break;
		default:
			break;
	}
}

//Practica 2
Collision Block::hit(const SDL_Rect& region, Collision::Target target)
{
	// Calcula la intersección
	SDL_Rect intersection;
	SDL_Rect ownRect = getCollisionRect();
	bool hasIntersection = SDL_IntersectRect(&ownRect, &region, &intersection);

	if (hasIntersection) {
		Collision collision{ Collision::OBSTACLE, intersection.w, intersection.h };

		// [...] Manejo del efecto del bloque

		return collision;
	}

	return NO_COLLISION;
}