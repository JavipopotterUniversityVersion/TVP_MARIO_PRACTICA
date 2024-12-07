#include "GameState.h"
#include "SDL_App.h"
#include <iostream>

void GameState::addEventListener(EventHandler* handler)
{
}

void GameState::addObject(GameObject* obj)
{
	gameObjects.push_back(obj);
}

void GameState::render() const
{
	for (auto it : gameObjects)
	{
		it->render();
	}
}

void GameState::update()
{
	for (auto it : gameObjects)
	{
		it->update();
	}
}