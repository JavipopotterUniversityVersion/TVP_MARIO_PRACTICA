#include "Button.h"
#include <iostream>

using Callback = std::function<void(void)>;

Button::Button(GameState* app, int x, int y, SDL_App::TextureName name) : GameObject(app)
{
	x -= WIDTH / 2;
	y -= HEIGHT / 2;

	position.Set(x, y);
	texture = game->getApp()->getTexture(name);
}

bool Button::isInside(Vector2D<int> pos) const
{
	return pos.getX() > position.getX() && pos.getX() < position.getX() + WIDTH
		&& pos.getY() > position.getY() && pos.getY() < position.getY() + HEIGHT;
}

void Button::handleEvent(const SDL_Event& event)
{
	int x;
	int y;

	SDL_GetMouseState(&x, &y);
	Vector2D<int> mousePos(x, y);

	if (isInside(mousePos))
	{
		_onHover(position.getX() - WIDTH / 2, position.getY() - HEIGHT / 2);

		if (event.type == SDL_MOUSEBUTTONDOWN) _onClick();
	}
}

void Button::render() const
{
	SDL_Rect rect{ position.getX(), position.getY(), WIDTH, HEIGHT};
	texture->renderFrame(rect, 0, 0);
}

void Button::update()
{
}