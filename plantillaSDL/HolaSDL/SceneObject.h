#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include <SDL.h>
#include "gameList.h"
#include <iostream>
#include "Collision.h"
#include "Texture.h"
class Game;

class SceneObject : public GameObject
{
	protected:
		Vector2D<float> position;
		Vector2D<float> size;
		Vector2D<float> velocity;
		GameList<SceneObject>::anchor anchor;

		const float SPEED_LIMIT = 3;
		const float MOVE_PERIOD = 1;

		Texture* texture;
		Vector2D<int> frameRange;
		int currentFrame = 0;

		float moveDelay = 0.5f;
		bool active = true;
	public:
		virtual Collision hit(SDL_Rect rect, Collision::Target target) = 0;
		SceneObject(Game* game, int x, int y);

		/*void setListAnchor(GameList<SceneObject>::anchor&& anchor)
		{
			this->anchor = std::move(anchor);
		}*/

		Collision tryToMove(Vector2D<float> direction, Collision::Target target);
		SDL_Rect getCollisionRect();

		void update() override;
		void render() override;

		Game* getGame() { return game; }
};

