#pragma once
#include "Pickable.h"

class Coin : public Pickable
{
	protected:
		void triggerAction() override;
};

