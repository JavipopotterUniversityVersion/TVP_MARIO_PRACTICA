#pragma once
#include "SceneObject.h"

class Enemy : public SceneObject
{
	public:
		void update() override;
		Enemy(PlayState* game, int x, int y) : SceneObject(game, x, y) { frameRange.Set(0,1); };
		Collision hit(const SDL_Rect& region, Collision::Target target) override;
		SceneObject* clone() override = 0;
};

