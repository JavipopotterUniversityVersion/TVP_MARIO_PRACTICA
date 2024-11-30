#pragma once
#include "SceneObject.h"

class Lift : public SceneObject
{
	private:
		float speed = 0.1f;

	public:
		Lift(Game* game, int x, int y, int direction);
		void update() override;
		SceneObject* clone() override;
		Collision hit(const SDL_Rect& rect, Collision::Target target) override;
		void render() override;
		SDL_Rect getCollisionRect() const override;
};

