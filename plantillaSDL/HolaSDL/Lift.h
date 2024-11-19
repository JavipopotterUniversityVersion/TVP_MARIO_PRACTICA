#pragma once
#include "SceneObject.h"

class Lift : public SceneObject
{
	private:
		float speed = 5;

	public:
		void update() override;
};

