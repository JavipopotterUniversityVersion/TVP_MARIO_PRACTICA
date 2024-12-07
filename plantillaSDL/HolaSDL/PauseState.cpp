#include "PauseState.h"
#include "Button.h"
#include "MainMenuState.h"

PauseState::PauseState(SDL_App* app) : UI_State(app, SDL_App::BACKGROUND)
{
	Button* continuar = new Button(this, SDL_App::WIN_WIDTH / 2, SDL_App::WIN_HEIGHT / 2 - 50, SDL_App::CONTINUAR);
	Button* mainMenu = new Button(this, SDL_App::WIN_WIDTH / 2, SDL_App::WIN_HEIGHT / 2 - 150, SDL_App::VOLVER_AL_MENU);
	Button* exit = new Button(this, SDL_App::WIN_WIDTH / 2, SDL_App::WIN_HEIGHT / 2, SDL_App::SALIR);

	continuar->connect([this]() {
		this->getApp()->popState();
		});
	mainMenu->connect([this]() {
		MainMenuState* mainMenu = new MainMenuState(this->getApp());
		this->getApp()->replaceState(mainMenu);
		});
	exit->connect([this]() {
		this->getApp()->exit();
		});

	continuar->setOnHover([this](int x, int y) {
		this->setPointer(x, y);
		});
	mainMenu->setOnHover([this](int x, int y) {
		this->setPointer(x, y);
		});
	exit->setOnHover([this](int x, int y) {
		this->setPointer(x, y);
		});

	gameObjects.push_back(continuar);
	gameObjects.push_back(mainMenu);
	gameObjects.push_back(exit);
}