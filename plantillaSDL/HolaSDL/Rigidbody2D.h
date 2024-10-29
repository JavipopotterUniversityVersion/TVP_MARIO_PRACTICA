#pragma once
#include "Vector2D.h"

enum Layer
{
	PLAYER, ENEMY, BLOCK
};

enum BodyType
{
	DYNAMIC, STATIC
};

class Rigidbody2D
{
	private:
		Vector2D<float> BoxSize;
		float gravity = 1;
		BodyType bodyType;
		Layer layer;


	public:
		void update();
};