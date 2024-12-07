#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include "Pickable.h"
class SDL_App;

class Mushroom : public Pickable
{
	static float constexpr SPEED = 2.0f;
	public:
		Mushroom(PlayState* game, int x, int y);
		SceneObject* clone() override;
		void triggerAction() override;
		void update() override;
};