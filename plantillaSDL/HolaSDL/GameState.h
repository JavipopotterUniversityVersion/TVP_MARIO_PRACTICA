#pragma once
#include "gameList.h"
#include "GameObject.h"
#include "EventHandler.h"
#include <list>
class SDL_App;

class GameState
{
private:
	SDL_App* app;
	GameList<GameObject> objectsList;
protected:
	int mapOffset = 0;
	list<EventHandler*> eventsList;
public:
	GameState(SDL_App* app) : app(app) {};
	void addEventListener();
	void addObject(GameObject obj);

	virtual void update();
	virtual void render() const;
	virtual void handleEvent(const SDL_Event&);

	SDL_App* getApp() const { return app; }
	int getMapOffset() const { return mapOffset; }
};

