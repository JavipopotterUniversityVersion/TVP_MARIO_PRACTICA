#pragma once
#include "GameObject.h"
#include "EventHandler.h"
#include <functional>

using Callback = std::function<void>;

class Button : public GameObject, public EventHandler
{
public:
	void connect(Callback callback) {}
};

