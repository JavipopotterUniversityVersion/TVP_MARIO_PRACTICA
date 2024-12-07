#pragma once
#include <array>
#include <SDL.h>
#include <vector>
#include "Player.h";
#include "Texture.h"
#include "Vector2D.h"
#include "gameList.h"
#include "Collision.h"
#include "Tilemap.h"
#include "GameStateMachine.h"
#include "SDL_App.h"

using uint = unsigned int;

class PlayState : public GameState
{
	bool seguir;
	bool exit = false;
	Player* player;
	Tilemap* map;

	SDL_App* app;

	std::vector<SceneObject*> objectQueue;
	int nextObject;

	bool loadNext = false;
	bool resetBool = false;
	int currentLevel = 1;

	int _mapOffset;

	void addVisibleObjects();
	void loadLevel(int levelIndex);

public:
	PlayState(SDL_App* app, int level);
	~PlayState();
	static const int TILE_SIDE = 32;

	void reset();
	void update() override;
	void handleEvent(const SDL_Event& event) override;

	void givePoints(int points) {};

	Collision checkCollision(SDL_Rect& rect, Collision::Target target);

	void addObject(SceneObject* object);

	Vector2D<float> ScreenToWorld(Vector2D<float> position) const;
	Vector2D<float> WorldToScreen(Vector2D<float> position) const;

	static constexpr uint WIN_WIDTH = 575;
	static constexpr uint WINDOW_WIDTH = 26;
	static constexpr uint WIN_HEIGHT = 500;
	static constexpr uint WINDOW_HEIGHT = 16;
	static constexpr uint FRAME_RATE = 50;

	void nextLevel();
	void setLoadFlag() { loadNext = true; }
	void resetFlag() { resetBool = true; }

	void goSuperMario();
	bool isSuperMario();

	void endgame() { seguir = false; }

	int getMapOffset() { return _mapOffset; }
};

