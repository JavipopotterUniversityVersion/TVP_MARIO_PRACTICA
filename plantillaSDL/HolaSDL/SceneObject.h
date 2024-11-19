#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include <SDL.h>
#include "gameList.h"
#include <iostream>

class SceneObject : public GameObject
{
	private:
		Vector2D<float> position;
		Vector2D<float> size;
		Vector2D<float> speed;
		GameList<SceneObject>::anchor anchor;

		int widht;
		int height;

	public:
		virtual void hit(SDL_Rect rect, bool isPlayer);

		void setListAnchor(GameList<SceneObject>::anchor&& anchor)
		{
			this->anchor = std::move(anchor);
		}
};

