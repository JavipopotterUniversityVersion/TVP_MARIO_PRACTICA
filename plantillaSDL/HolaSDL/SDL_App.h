#pragma once
#include <array>
#include <SDL.h>
#include <vector>
#include "Texture.h"
#include "gameStateMachine.h"

using uint = unsigned int;

class SDL_App : public GameStateMachine
{
	bool seguir = true;
public:
	static const int TILE_SIDE = 32;
	static constexpr float GRAVITY = 30.0f;
	enum TextureName {
		BACKGROUND,
		MARIO,
		SUPERMARIO,
		BLOCKS,
		GOOMBA,
		KOOPA,
		MUSHROOM,
		LIFT,
		COIN,
		CONTINUAR,
		GAME_OVER,
		HAS_GANADO,
		NIVEL1,
		NIVEL2,
		NOMBRE_MARIO,
		NUMBERS,
		SALIR,
		VOLVER_AL_MENU,
		PORTADA,
		NUM_TEXTURES,
	};

private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	std::array<Texture*, NUM_TEXTURES> textures;

public:
	Texture* getTexture(TextureName name) const;

	static constexpr uint WIN_WIDTH = 575;
	static constexpr uint WINDOW_WIDTH = 26;
	static constexpr uint WIN_HEIGHT = 500;
	static constexpr uint WINDOW_HEIGHT = 16;
	static constexpr uint FRAME_RATE = 50;

	void run();
	void render() const override;

	SDL_App();
	~SDL_App();

	SDL_Renderer* getRenderer() { return renderer; }
	void exit() { seguir = false; }
};

inline Texture*
SDL_App::getTexture(TextureName name) const
{
	return textures[name];
}