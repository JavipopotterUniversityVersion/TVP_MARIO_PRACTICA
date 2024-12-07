#pragma once
#include "SceneObject.h"
#include "Collision.h"

class Pickable : public SceneObject
{
	private:
		Collision::Target target;

	protected:
		virtual void triggerAction() = 0;

	public:
		Pickable(PlayState* game, int x, int y) : SceneObject(game, x, y) {};
		Collision hit(const SDL_Rect& rect, Collision::Target target) override;
};

