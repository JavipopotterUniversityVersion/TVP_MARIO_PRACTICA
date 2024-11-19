#pragma once
#include <array>
#include <SDL.h>
#include <vector>
#include "Texture.h"
#include "Tilemap.h"
#include "Vector2D.h"
#include "Player.h"
#include "Goomba.h"
#include "Koopa.h"
#include "Collision.h"
#include "Mushroom.h"
//#include "Block.h"
class Block;

using uint = unsigned int;

class Game
{
public:
	static const int TILE_SIZE = 32;
	static const int GRAVITY = 10;
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
	Mushroom* mushroom;
	vector<Goomba*> goombas;
	vector<Block*> blocks;
	Tilemap* map;
	std::array<Texture*, NUM_TEXTURES> textures;

public:
	void run();
	void reset();
	void update();
	void render() const;
	void handleEvents();
	void givePoints(int points);
	bool checkCollision(SDL_Rect& rect, Collision::Tag tag, bool superMario = false);

	Vector2D<float> ScreenToWorld(Vector2D<float> position) const;
	Vector2D<float> WorldToScreen(Vector2D<float> position) const;

	Texture* getTexture(TextureName name) const;

	static constexpr uint WIN_WIDTH = 575;
	static constexpr uint WINDOW_WIDTH = 26;
	static constexpr uint WIN_HEIGHT = 500;
	static constexpr uint WINDOW_HEIGHT = 16;
	static constexpr uint FRAME_RATE = 50;
	int GetMapOffset() const { return mapOffset; }

	void placeMushroom(int x, int y) { mushroom->place(x, y); }
	void endgame() { seguir = false; }

	Game();
	~Game();
};

inline Texture*
Game::getTexture(TextureName name) const
{
	return textures[name];
}