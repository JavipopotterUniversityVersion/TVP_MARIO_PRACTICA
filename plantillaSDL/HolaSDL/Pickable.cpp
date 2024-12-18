#include "Pickable.h"
#include "Collision.h"

Collision Pickable::hit(SDL_Rect rect, Collision::Target target)
{
	// Comprueba si hay colisión
	Collision collision;
	SDL_Rect ownRect = getCollisionRect();

	if (target == Collision::ENEMIES) {
		triggerAction();  // método protegido que implementará la subclase
		delete this;
	}

	return collision; // constante Collision{}
}