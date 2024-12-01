#pragma once
#include "SceneObject.h"
#include "Collision.h"
class SDL_App;

class Pickable : public SceneObject
{
	private:
		const Collision NO_COLLISION = {};
		Collision::Target target;

	protected:
		virtual void triggerAction() = 0;

	public:
		Pickable(SDL_App* game, int x, int y) : SceneObject(game, x, y) {};
		Collision hit(const SDL_Rect& rect, Collision::Target target) override;
};

