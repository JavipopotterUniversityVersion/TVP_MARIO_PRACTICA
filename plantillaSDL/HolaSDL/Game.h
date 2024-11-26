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

using uint = unsigned int;

class Game
{
public:
	static const int TILE_SIDE = 32;
	static constexpr float GRAVITY = 0.2f;
	enum TextureName {
		BACKGROUND,
		MARIO,
		SUPERMARIO,
		BLOCKS,
		GOOMBA,
		KOOPA,
		MUSHROOM,
		NUM_TEXTURES,
	};

private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	bool seguir;
	int mapOffset = 0;
	bool exit = false;
	Player* player;
	GameList<SceneObject> gameObjects;
	Tilemap* map;
	std::array<Texture*, NUM_TEXTURES> textures;

	std::vector<SceneObject*> objectQueue;
	int nextObject;

	void addVisibleObjects();

public:
	void run();
	void reset();
	void update();
	void render();
	void handleEvents();
	void givePoints(int points) {};
	Collision checkCollision(SDL_Rect& rect, Collision::Target target);

	Vector2D<float> ScreenToWorld(Vector2D<float> position) const;
	Vector2D<float> WorldToScreen(Vector2D<float> position) const;

	Texture* getTexture(TextureName name) const;

	static constexpr uint WIN_WIDTH = 575;
	static constexpr uint WINDOW_WIDTH = 26;
	static constexpr uint WIN_HEIGHT = 500;
	static constexpr uint WINDOW_HEIGHT = 16;
	static constexpr uint FRAME_RATE = 70;
	int GetMapOffset() const { return mapOffset; }
	void nextLevel();
	void loadLevel(string levelIndex);
	void addObject(SceneObject* obj);

	void endgame() { seguir = false; }

	Game();
	~Game();
};

inline Texture*
Game::getTexture(TextureName name) const
{
	return textures[name];
}