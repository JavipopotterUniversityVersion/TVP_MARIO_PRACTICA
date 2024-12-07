#include "UI_State.h"
#include "Button.h"
#include <iostream>

UI_State::UI_State(SDL_App* app, SDL_App::TextureName backgName) : GameState(app), background(app->getTexture(backgName)),
mushroom(app->getTexture(SDL_App::MUSHROOM)) {
	pointerPosition.Set(-10, -10);
}

void UI_State::handleEvent(const SDL_Event& event)
{
	SDL_Event evento = event;
	while (SDL_PollEvent(&evento)) {
		for (auto obj : gameObjects)
		{
			Button* button = static_cast<Button*>(obj);
			button->handleEvent(evento);
		}
	}
}

void UI_State::render() const
{
	background->render();

	SDL_Rect mushroomRect{ pointerPosition.getX(), pointerPosition.getY(), SDL_App::TILE_SIDE, SDL_App::TILE_SIDE };
	mushroom->renderFrame(mushroomRect, 0, 0);

	GameState::render();
}