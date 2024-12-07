#pragma once
#include "SceneObject.h"
class Bullet : public SceneObject
{
	static constexpr float SPEED = 35.0f;
public:
	Bullet(PlayState* game, int x, int y, Vector2D<float> direction);
	SceneObject* clone() override { return this; };
	Collision hit(const SDL_Rect& region, Collision::Target target) override;
	void update() override;
};

