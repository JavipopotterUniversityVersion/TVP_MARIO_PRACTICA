#pragma once
#include "GameObject.h"
#include "EventHandler.h"

using Callback = std::function<void(void)>;

class Button : public GameObject, public EventHandler
{
public:
	void connect(Callback callback)
};

