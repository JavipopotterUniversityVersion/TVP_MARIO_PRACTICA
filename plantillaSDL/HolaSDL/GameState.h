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
protected:
	GameList<GameObject> gameObjects;
	std::list<EventHandler*>eventsList;
public:		
	GameState(SDL_App* app) : app(app) {};

	virtual void render() const;
	virtual void update();
	virtual void handleEvent(const SDL_Event&) = 0;

	void addEventListener(EventHandler* handler);
	void addObject(GameObject* obj);

	SDL_App* getApp() const { return app; }
};

