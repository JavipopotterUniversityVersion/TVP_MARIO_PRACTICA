#include "MainMenuState.h"
#include "PlayState.h"
#include "Button.h"
#include "Player.h"
#include <iostream>
#include "SDL_App.h"

MainMenuState::MainMenuState(SDL_App* app) : UI_State(app, SDL_App::PORTADA)
{
	Button* level1 = new Button(this, SDL_App::WIN_WIDTH/2, SDL_App::WIN_HEIGHT/2 + 25, SDL_App::NIVEL1);
	Button* level2 = new Button(this, SDL_App::WIN_WIDTH/2, SDL_App::WIN_HEIGHT/2 + 125, SDL_App::NIVEL2);
	Button* exit = new Button(this, SDL_App::WIN_WIDTH / 2, SDL_App::WIN_HEIGHT / 2 + 225, SDL_App::SALIR);

	level1->connect([this]() {
		this->getApp()->replaceState(new PlayState(this->getApp(), 1));
		});
	level2->connect([this]() {
		this->getApp()->replaceState(new PlayState(this->getApp(), 2));
		});
	exit->connect([this]() {
		this->getApp()->exit();
		});

	level1->setOnHover([this](int x,int y) {
		this->setPointer(x, y);
		});
	level2->setOnHover([this](int x, int y) {
		this->setPointer(x, y);
		});
	exit->setOnHover([this](int x, int y) {
		this->setPointer(x, y);
		});

	gameObjects.push_back(level1);
	gameObjects.push_back(level2);
	gameObjects.push_back(exit);

	pointerPosition.Set(0, 0);
}