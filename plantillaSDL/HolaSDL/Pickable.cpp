#include "Pickable.h"
#include "Collision.h"

Collision Pickable::hit(const SDL_Rect& region, Collision::Target target)
{
	// Comprueba si hay colisión
	Collision col;
	SDL_Rect ownRect = getCollisionRect();

	if (target == Collision::ENEMIES && SDL_HasIntersection(&ownRect, &region)) {
		triggerAction();  // método protegido que implementará la subclase
		delete this;
	}

	return col; // constante Collision{}
}