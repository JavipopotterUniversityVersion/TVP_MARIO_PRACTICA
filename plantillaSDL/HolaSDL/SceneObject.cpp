#include "SceneObject.h"
#include "Collision.h"
// El m�todo protegido tryToMove concentra el c�digo de la comprobaci�n
// de las colisiones para todos los objetos del juego. Recibe un vector
// con el movimiento que se quiere aplicar al objeto, prueba el movimiento
// en cambos ejes y devuelve la informaci�n de tipo Collision.

Collision SceneObject::tryToMove(const Vector2D<>& speed, Collision::Target target)
{
	Collision collision;
	SDL_Rect rect = getCollisionRect();

	// Intenta moverse en vertical
	if (speed.getY() != 0) {
		rect.y += speed.getY();

		collision = game->checkCollision(rect, target);

		// Cantidad que se ha entrado en el obst�culo (lo que hay que deshacer)
		int fix = collision.vertical * (speed.getY() > 0 ? 1 : -1);
		_position += {0, speed.getY() - fix};

		rect.y -= fix; // recoloca la caja para la siguiente colisi�n
	}

	collision.horizontal = 0; // la horizontal del choque vertical da igual

	// Intenta moverse en horizontal
	if (speed.getX() != 0) {
		rect.x += speed.getX();

		Collision partial = game->checkCollision(rect, target);

		// Copia la informaci�n de esta colisi�n a la que se devolver�
		collision.horizontal = partial.horizontal;

		if (partial.result == Collision::DAMAGE)
			collision.result = Collision::DAMAGE;

		_position += {speed.getX() - collision.horizontal * (speed.getX() > 0 ? 1 : -1), 0};
	}

	return collision;
}

SDL_Rect SceneObject::getCollisionRect() const
{
	return SDL_Rect{
		_position.getX(),
		_position.getY() - _height,  // la referencia es la esquina inferior izquierda
		_width,
		_height
	};
}

SDL_Rect
SceneObject::getRenderRect() const
{
	return SDL_Rect{
		_position.getX() - game->getMapOffset(),  // coordenadas de la ventana
		_position.getY() - _height,
		_width,
		_height
	};
}