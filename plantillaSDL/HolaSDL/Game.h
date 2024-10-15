#pragma once
#include <array>
#include <SDL.h>
#include "Texture.h"

using uint = unsigned int;

class Game
{
public:
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
	std::array<Texture*, NUM_TEXTURES> textures;
	bool seguir;
	int mapOffset = 0;

public:
	void run();

	void update();
	void render() const;
	void handleEvents();

	Texture* getTexture(TextureName name) const;

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
