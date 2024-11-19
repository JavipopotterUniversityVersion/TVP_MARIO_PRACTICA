#pragma once
#include "SceneObject.h"
#include "Collision.h"

class Pickable : public SceneObject
{
	private:
		const Collision NO_COLLISION = {};
		Collision::Target target;
		SDL_Rect region;

	protected:
		virtual void triggerAction();

	public:
		Collision hit(SDL_Rect rect, bool isPlayer) override;
};

