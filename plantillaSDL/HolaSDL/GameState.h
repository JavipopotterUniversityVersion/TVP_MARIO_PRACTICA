#pragma once
#include "gameList.h"
#include "GameObject.h"
#include "EventHandler.h"
#include <list>
class SDL_App;

class GameState
{
private:
	SDL_App* game;
	GameList<GameObject> objectsList;
	list<EventHandler*> eventsList;
public:
	void addEventListener();
	void addObject();

	virtual void update();
	virtual void render() const;
	virtual void handleEvent();
};

