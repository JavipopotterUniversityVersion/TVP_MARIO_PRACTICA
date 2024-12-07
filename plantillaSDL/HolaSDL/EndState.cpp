#include "EndState.h"
#include "Button.h"
#include "MainMenuState.h"

EndState::EndState(SDL_App* app) : UI_State(app, SDL_App::FONDO_NEGRO)
{
	Button* menu = new Button(this, SDL_App::WIN_WIDTH / 2, SDL_App::WIN_HEIGHT / 2, SDL_App::VOLVER_AL_MENU);
	Button* exit = new Button(this, SDL_App::WIN_WIDTH / 2, SDL_App::WIN_HEIGHT / 2 + 50, SDL_App::SALIR);

	menu->connect([this]() {
		this->getApp()->replaceState(new MainMenuState(this->getApp()));
		});
	exit->connect([this]() {
		this->getApp()->exit();
		});

	menu->setOnHover([this](int x, int y) {
		this->setPointer(x, y);
		});
	exit->setOnHover([this](int x, int y) {
		this->setPointer(x, y);
		});

	gameObjects.push_back(menu);
	gameObjects.push_back(exit);

	gameOverTexture = app->getTexture(SDL_App::GAME_OVER);
}

void EndState::render() const
{
	UI_State::render();

	SDL_Rect rect{
		SDL_App::WIN_WIDTH / 2,
		SDL_App::WINDOW_HEIGHT / 3,
		SDL_App::TILE_SIDE * 3,
		SDL_App::TILE_SIDE
	};

	gameOverTexture->renderFrame(rect, 0, 0);
}