#include "Pickable.h"
#include "Collision.h"

Collision Pickable::hit(SDL_Rect rect, Collision::Target target)
{
	// Comprueba si hay colisi�n
	Collision collision;
	SDL_Rect ownRect = getCollisionRect();

	if (target == Collision::ENEMIES) {
		triggerAction();  // m�todo protegido que implementar� la subclase
		delete this;
	}

	return collision; // constante Collision{}
}