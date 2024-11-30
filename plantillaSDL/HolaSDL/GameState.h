#pragma once
#include "gameList.h"
#include "GameObject.h"
#include <list>
class Game;

class GameState
{
private:
	Game* game;
	GameList<GameObject> objectsList;
	list<EventHandler*> eventsList;
public:
	void addEventListener();
	void addObject();

	virtual void update();
	virtual void render() const;
	virtual void handleEvent(const SDL_Event& event);
};

