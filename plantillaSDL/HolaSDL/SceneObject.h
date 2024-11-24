#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include <SDL.h>
#include "gameList.h"
#include <iostream>
#include "Collision.h"
#include "Texture.h"

class SceneObject : public GameObject
{
	protected:
		Vector2D<float> position;
		Vector2D<float> size;
		Vector2D<float> velocity;
		GameList<SceneObject>::anchor anchor;

		const float SPEED_LIMIT;
		const float MOVE_PERIOD;

		Texture* texture;
		Vector2D<int> frameRange;
		int currentFrame = 0;

		float moveDelay;
	public:
		virtual Collision hit(SDL_Rect rect, Collision::Target);

		void setListAnchor(GameList<SceneObject>::anchor&& anchor)
		{
			this->anchor = std::move(anchor);
		}

		Collision tryToMove(Vector2D<float> direction, Collision::Target target);
		SDL_Rect getCollisionRect();

		void render() override;
};

