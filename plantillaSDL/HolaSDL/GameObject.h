#pragma once
#include "Vector2D.h"
#include "gameList.h"
class GameState;

class GameObject
{ 
	protected:
		Vector2D<float> position;
		GameState* game;
		GameList<GameObject>::anchor anchor;

	public:
		GameObject(GameState* game) : game(game) {};
		virtual void render() const = 0;
		virtual void update() = 0;

		void setListAnchor(GameList<GameObject>::anchor&& anchor)
		{
			this->anchor = std::move(anchor);
		}
};

