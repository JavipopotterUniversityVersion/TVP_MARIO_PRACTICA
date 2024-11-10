#pragma once
#include "Vector2D.h"
#include "SDL.h"

struct Collision
{
	enum Tag
	{
		MARIO,
		ENEMY,
		BLOCK
	};
	Tag tag;
};