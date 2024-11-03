#pragma once
#include <array>
#include <SDL.h>
#include <vector>
#include "Texture.h"
#include "Tilemap.h"
#include "Vector2D.h"
#include "Player.h"
#include "Goomba.h"

using uint = unsigned int;

class Game
{
public:
	static const int TILE_SIZE = 32;
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
	vector<Goomba*> goombas;
	Tilemap* map;
	std::array<Texture*, NUM_TEXTURES> textures;

public:
	void run();

	void update();
	void render() const;
	void handleEvents();

	Texture* getTexture(TextureName name) const;

	static constexpr uint WIN_WIDTH = 575;
	static constexpr uint WINDOW_WIDTH = 26;
	static constexpr uint WIN_HEIGHT = 500;
	static constexpr uint WINDOW_HEIGHT = 16;
	static constexpr uint FRAME_RATE = 50;
	static constexpr uint FLOOR_HEIGHT = 13;

	int GetMapOffset() const { return mapOffset; }

	Game();
	~Game();
};

inline Texture*
Game::getTexture(TextureName name) const
{
	return textures[name];
}
