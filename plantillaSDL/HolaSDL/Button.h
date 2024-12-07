#pragma once
#include "GameObject.h"
#include "EventHandler.h"
#include <functional>
#include "Texture.h"
#include "SDL_App.h"

using Callback = std::function<void(void)>;
using HoverCallback = std::function<void(int, int)>;

class Button : public GameObject, public EventHandler
{
	static const int WIDTH = 128;
	static const int HEIGHT = 32;

	Texture* texture;
	bool isInside(Vector2D<int> pos) const;

	Callback _onClick;
	HoverCallback _onHover;
public:
	Button(GameState* app, int x, int y, SDL_App::TextureName name);
	void handleEvent(const SDL_Event& event) override;
	void render() const override;
	void update() override;

	void connect(Callback callback) { _onClick = callback; }
	void setOnHover(HoverCallback func) { _onHover = func; }
};

