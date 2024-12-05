#pragma once
#include "GameObject.h"
#include "EventHandler.h"
#include <functional>

using Callback = std::function<void(void)>;

class Button : public GameObject, public EventHandler
{
	Callback callback;
public:
	void connect(Callback callback) {}
	void handleEvent(const SDL_Event& event) override;
};

