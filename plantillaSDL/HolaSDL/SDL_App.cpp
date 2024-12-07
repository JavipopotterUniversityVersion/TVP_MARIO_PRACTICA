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
#include "PlayState.h"
#include "PauseState.h"
#include "MainMenuState.h"
#include "EndState.h"

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

//CONTINUAR,
//GAME_OVER,
//HAS_GANADO,
//NIVEL1,
//NIVEL2,
//NOMBRE_MARIO,
//NUMBERS,
//SALIR,
//VOLVER_AL_MENU,

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
	TextureSpec{"coin.png", 4, 1},
	TextureSpec{"continuar.png", 1, 1},
	TextureSpec{"gameOver.png", 1, 1},
	TextureSpec{"hasGanado.png", 1, 1},
	TextureSpec{"nivel1.png", 1, 1},
	TextureSpec{"nivel2.png", 1, 1},
	TextureSpec{"nombreMario.png", 1, 1},
	TextureSpec{"numbers.png", 10, 1},
	TextureSpec{"salir.png", 1, 1},
	TextureSpec{"volverAlMenú.png", 1, 1},
	TextureSpec{"portada.png", 1, 1}
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


	MainMenuState* mainMenu = new MainMenuState(this);
	pushState(mainMenu);
}

void SDL_App::run()
{
	while (seguir) {

		// Marca de tiempo del inicio de la iteraciÃ³n
		uint32_t inicio = SDL_GetTicks();

		update();
		render();
		SDL_Event evento;
		handleEvent(evento);

		// Tiempo que se ha tardado en ejecutar lo anterior
		uint32_t elapsed = SDL_GetTicks() - inicio;

		// Duerme el resto de la duración del frame
		if (elapsed < FRAME_RATE)
			SDL_Delay(FRAME_RATE - elapsed);
	}
}

void SDL_App::render() const
{
	SDL_RenderClear(renderer);
	GameStateMachine::render();
	SDL_RenderPresent(renderer);
}