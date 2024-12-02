#pragma once
#include "Pickable.h"

class Coin : public Pickable
{
	protected:
		void triggerAction() override;
	public:
		Coin(PlayState* game, int x, int y);
		Coin(Coin& coin);
		SceneObject* clone() override;
};

