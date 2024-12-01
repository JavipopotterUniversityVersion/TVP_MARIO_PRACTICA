#include "SceneObject.h"
#include "Texture.h"
#include "SDL.h"
#include "SDL_App.h"
#include "PlayState.h"

SceneObject::SceneObject(PlayState* game, int x, int y)
{
	this->game = game;
	position.Set(x, y);
}

SDL_Rect SceneObject::getRenderRect() const
{
	return SDL_Rect{
		int(position.getX() - game->getMapOffset()),  // coordenadas de la ventana
		int(position.getY() - _height),
		_width,
		_height
	};
}

SDL_Rect SceneObject::getCollisionRect() const
{
	return SDL_Rect{
		int(position.getX()),
		int(position.getY() - _height),  // la referencia es la esquina inferior izquierda
		_width,
		_height
	};
}


void SceneObject::render() const
{
	/*currentFrame++;

	if (currentFrame > frameRange.getY() || currentFrame < frameRange.getX())
	{
		currentFrame = frameRange.getX();
	}*/

	SDL_Rect rect = getRenderRect();
	texture->renderFrame(rect, 0, currentFrame);
}


Collision SceneObject::tryToMove(const Vector2D<float>&speed, Collision::Target target)
{
		Collision collision;
		SDL_Rect rect = getCollisionRect();

		// Intenta moverse en vertical
		if (speed.getY() != 0) {
			rect.y += speed.getY();

			collision = game->checkCollision(rect, target);

			// Cantidad que se ha entrado en el obstáculo (lo que hay que deshacer)
			int fix = collision.vertical * (speed.getY() > 0 ? 1 : -1);
			position += {0, speed.getY() - fix};

			// Obs: a ? b : c es el operador ternario: vale b si a es cierto y c en caso contrario

			rect.y -= fix; // recoloca la caja para la siguiente colisión
		}

		collision.horizontal = 0; // la horizontal del choque vertical da igual

		// Intenta moverse en horizontal
		// (podría ser conveniente comprobar colisiones incluso aunque el objeto estuviera parado)
		if (speed.getX() != 0) {
			rect.x += speed.getX();

			Collision partial = game->checkCollision(rect, target);

			// Copia la información de esta colisión a la que se devolverá
			collision.horizontal = partial.horizontal;

			if (partial.result == Collision::DAMAGE)
				collision.result = Collision::DAMAGE;

			position += {speed.getX() - collision.horizontal * (speed.getX() > 0 ? 1 : -1), 0};
		}

		return collision;
}

void SceneObject::update()
{
	position.Set(position.getX() + velocity.getX(), position.getY() + velocity.getY());
}