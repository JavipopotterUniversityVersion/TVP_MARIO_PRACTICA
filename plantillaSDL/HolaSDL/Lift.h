#pragma once
#include "SceneObject.h"

class Lift : public SceneObject
{
	private:
		float speed = 0.15f;

	public:
		Lift(Game* game, int x, int y);
		void update() override;
		SceneObject* clone() override;
		Collision hit(SDL_Rect rect, Collision::Target target) override;
		void render() override;
};

