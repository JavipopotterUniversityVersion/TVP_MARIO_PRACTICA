#pragma once
#include "SceneObject.h"
class Game;

class Enemy : public SceneObject
{
	public:
		void update() override;
		Enemy(Game* game, int x, int y) : SceneObject(game, x, y) { frameRange.Set(0,1); };
		Collision hit(SDL_Rect rect, Collision::Target target) override;
		SceneObject* clone() override = 0;
};

