#pragma once
#include "gameList.h"
#include "GameObject.h"
#include <list>
#include "EventHandler.h"
class SDL_App;

class GameState
{
private:
	SDL_App* app;
	GameList<GameObject> objectsList;
protected:
	//list<EventHandler*>eventsList;
public:
	GameState(SDL_App* app) : app(app) {};

	virtual void render() const = 0;
	virtual void update() = 0;
	virtual void handleEvent(const SDL_Event&) = 0;

	void addEventListener(EventHandler* handler);
	void addObject(GameObject* obj);

	SDL_App* getApp() const { return app; }
};

