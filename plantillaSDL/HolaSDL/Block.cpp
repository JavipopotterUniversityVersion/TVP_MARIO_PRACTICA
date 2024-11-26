#include "Block.h"
#include "Game.h"
#include "Collision.h"

//Practica 2
Collision Block::hit(SDL_Rect rect, Collision::Target target)
{

	SDL_Rect intersection;
	SDL_Rect thisRect = getCollisionRect();
	SDL_IntersectRect(&rect, &thisRect, &intersection);

	Collision collision{ Collision::OBSTACLE, intersection.w, intersection.h };
	collision.vertical = position.getY();

	if (rect.y > position.getY())
	{
		switch (type)
		{
		case SORPRESA:
			if (action == POTENCIADOR)
			{
			}
			else
			{
			}
			frameRange.Set(4, 4);
			type = VACIO;
			break;
		case OCULTO:
			frameRange.Set(4, 4);
			type = VACIO;
			break;
		case LADRILLO:
			break;
		default:
			break;
		}
	}

	return collision;
}

void Block::render()
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

Block::Block(Game* game, int x, int y, BlockType type, BlockAction action) : SceneObject(game, x, y), type(type), action(action) 
{ 
	texture = game->getTexture(Game::BLOCKS);

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