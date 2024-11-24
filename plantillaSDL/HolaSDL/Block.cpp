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

	return collision;
}

void Block::render()
{
	texture->renderFrame(getCollisionRect(), 0, int(type));
}