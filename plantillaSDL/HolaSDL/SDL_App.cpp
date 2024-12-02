#include "SDL_App.h"
#include "Entity.h"
#include "Player.h"
#include "Goomba.h"
#include "Tilemap.h"
#include "Block.h"
#include "Collision.h"
#include "SceneObject.h"
#include "Lift.h"
#include "SDLError.h"
#include "FileNotFoundError.h"
#include "FileFormatError.h"

#include <iostream>
#include <fstream>
using namespace std;

struct TextureSpec
{
	const char* name;	// Ruta del archivo
	uint numColumns;	// Número de frames por fila
	uint numRows;		// Número de frames por columna
};

// Directorio raíz de los archivos de textura
const string textureRoot = "../Assets/images/";

// Especificación de las texturas del juego
const array<TextureSpec, SDL_App::NUM_TEXTURES> textureSpec{
	TextureSpec{"background.png", 9, 7},
	TextureSpec{"mario.png", 12, 1},
	TextureSpec{"supermario.png", 22, 1},
	TextureSpec{"blocks.png", 6, 1},
	TextureSpec{"goomba.png", 3, 1},
	TextureSpec{"koopa.png", 4, 1},
	TextureSpec{"mushroom.png", 1, 1},
	TextureSpec{"lift.png", 1, 1},
	TextureSpec{"coin.png", 4, 1}
};

SDL_App::~SDL_App()
{
	for (Texture* texture : textures) delete texture;
	delete renderer;
	delete window;
}

SDL_App::SDL_App()
{
	try
	{
		// Inicializa la SDL
		SDL_Init(SDL_INIT_EVERYTHING);
		window = SDL_CreateWindow("First test with SDL",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			WIN_WIDTH,
			WIN_HEIGHT,
			SDL_WINDOW_SHOWN);
		if (window == nullptr) throw SDLError(SDL_GetError());
	}
	catch (const SDLError& e)
	{
		cout << e.what() << endl;
	}

	try
	{
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer == nullptr) throw SDLError(SDL_GetError());
	}
	catch (const SDLError& e)
	{
		cout << e.what() << endl;
	}

	// Carga las texturas
	for (int i = 0; i < NUM_TEXTURES; ++i)
	{
		textures[i] = new Texture(renderer,
			(textureRoot + textureSpec[i].name).c_str(),
			textureSpec[i].numRows, textureSpec[i].numColumns);
	}
}

void SDL_App::run()
{
	update();
	render();
	//handleEvent();
}