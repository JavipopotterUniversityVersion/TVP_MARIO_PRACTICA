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

using uint = unsigned int;

class PlayState : public GameState
{
	bool seguir;
	int mapOffset = 0;
	bool exit = false;
	Player* player;
	GameList<SceneObject> gameObjects;
	Tilemap* map;

	std::vector<SceneObject*> objectQueue;
	int nextObject;

	bool loadNext = false;
	bool resetBool = false;
	int currentLevel = 1;

	void addVisibleObjects();
	void loadLevel(int levelIndex);

public:
	void run();
	void reset();
	void update() override;
	void render() const override;
	void handleEvent(const SDL_Event& event) override;
	void givePoints(int points) {};
	Collision checkCollision(SDL_Rect& rect, Collision::Target target);

	Vector2D<float> ScreenToWorld(Vector2D<float> position) const;
	Vector2D<float> WorldToScreen(Vector2D<float> position) const;

	static constexpr uint WIN_WIDTH = 575;
	static constexpr uint WINDOW_WIDTH = 26;
	static constexpr uint WIN_HEIGHT = 500;
	static constexpr uint WINDOW_HEIGHT = 16;
	static constexpr uint FRAME_RATE = 50;
	int getMapOffset() const { return mapOffset; }
	void nextLevel();
	void setLoadFlag() { loadNext = true; }
	void resetFlag() { resetBool = true; }

	void goSuperMario();
	bool isSuperMario();

	void endgame() { seguir = false; }
};

