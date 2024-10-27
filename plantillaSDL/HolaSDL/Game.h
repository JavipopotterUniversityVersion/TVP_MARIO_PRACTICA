#pragma once
#include <array>
#include <SDL.h>
#include "Texture.h"
#include "Tilemap.h"
#include "Vector2D.h"
#include "Entity.h"
#include "Player.h"

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
	Tilemap* map;
	std::array<Texture*, NUM_TEXTURES> textures;

public:
	void run();

	void update();
	void render() const;
	void handleEvents();

	Texture* getTexture(TextureName name) const;
	int getMapOffset() { return mapOffset; }

	static constexpr uint WIN_WIDTH = 800;
	static constexpr uint WIN_HEIGHT = 600;
	static constexpr uint FRAME_RATE = 50;

	int GetMapOffset() const { return mapOffset; }

	Game();
	~Game();
};

inline Texture*
Game::getTexture(TextureName name) const
{
	return textures[name];
}
