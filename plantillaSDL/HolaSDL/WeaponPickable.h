#pragma once
#include "Pickable.h"
#include "Weapon.h"
class WeaponPickable : public Pickable
{
	Weapon* weapon;
public:
	WeaponPickable(PlayState* game, int x, int y, Weapon* weapon);
	void triggerAction() override;
	SceneObject* clone() override { return this; }
};

