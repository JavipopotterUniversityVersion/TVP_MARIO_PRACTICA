#include "Block.h"
#include "GameState.h"
#include "Collision.h"
#include "Mushroom.h"
#include "Coin.h"

//Practica 2
Collision Block::hit(const SDL_Rect& region, Collision::Target target)
{

	// Calcula la intersección
	SDL_Rect intersection;
	SDL_Rect ownRect = getCollisionRect();
	bool hasIntersection = SDL_IntersectRect(&ownRect, &region, &intersection);

	if (hasIntersection && region.y > ownRect.y)
	{
		Collision collision{ Collision::OBSTACLE, intersection.w, intersection.h };
		switch (type)
		{
		case SORPRESA:
			if (action == POTENCIADOR)
			{
				//game->addObject(new Mushroom(playState, position.getX(), position.getY() - 1));
			}
			else
			{
				//game->addObject(new Coin(playState, position.getX(), position.getY() - 1));
			}
			frameRange.Set(4, 4);
			type = VACIO;
			break;
		case OCULTO:
			frameRange.Set(4, 4);
			type = VACIO;
			break;
		case LADRILLO:
			//if (game->isSuperMario()) delete this;
			break;
		default:
			break;
		}
	}

	return Collision{};
}

void Block::render() const
{
	if (type != OCULTO)
	{
		SceneObject::render();
	}
}

SceneObject* Block::clone()
{
	return new Block(*this);
}

Block::Block(GameState* game, int x, int y, BlockType type, BlockAction action) : SceneObject(playState, x, y), type(type), action(action) 
{ 
	texture = game->getApp()->getTexture(SDL_App::BLOCKS);

	switch (type)
	{
	case SORPRESA:
		frameRange.Set(0, 3);
		break;
	case OCULTO:
		break;
	case VACIO:
		frameRange.Set(4, 4);
		break;
	case LADRILLO:
		frameRange.Set(5, 5);
		break;
	default:
		break;
	}
};