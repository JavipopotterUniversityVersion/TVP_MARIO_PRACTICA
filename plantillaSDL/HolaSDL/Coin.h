#pragma once
#include "Pickable.h"

class Coin : public Pickable
{
	protected:
		void triggerAction() override;
	public:
		Coin(SDL_App* game, int x, int y);
		Coin(Coin& coin);
		SceneObject* clone() override;
};

