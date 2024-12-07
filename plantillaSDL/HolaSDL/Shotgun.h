#pragma once
#include "Weapon.h"
class Shotgun : public Weapon
{
	const int offsets[5] = { -45, -13, 0, 23, 45 };
public:
	Shotgun(PlayState* game, SceneObject* father = nullptr);
	void Use() override;
};

