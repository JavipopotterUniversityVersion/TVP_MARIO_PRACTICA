#pragma once
#include "SceneObject.h"
#include "Collision.h"
class Game;

class Pickable : public SceneObject
{
	private:
		const Collision NO_COLLISION = {};
		Collision::Target target;

	protected:
		virtual void triggerAction() = 0;

	public:
		Pickable(Game* game, int x, int y) : SceneObject(game, x, y) {};
		Collision hit(const SDL_Rect& rect, Collision::Target target) override;
};

