#include <string>

#include "Game.h"
#include "Entity.h"
#include "Player.h"
#include "Goomba.h"
#include "Koopa.h"
#include "Tilemap.h"

using namespace std;

struct TextureSpec
{
	const char* name;	// Ruta del archivo
	uint numColumns;	// Número de frames por fila
	uint numRows;		// Número de frames por columna
};

// Directorio raíz de los archivos de textura
const string textureRoot = "../Assets/imgs/";

// Especificación de las texturas del juego
const array<TextureSpec, Game::NUM_TEXTURES> textureSpec{
	TextureSpec{"background.png", 9, 7},
	TextureSpec{"mario.png", 12, 1},
	TextureSpec{"supermario.png", 22, 1},
	TextureSpec{"blocks.png", 6, 1},
	TextureSpec{"goomba.png", 3, 1},
	TextureSpec{"koopa.png", 4, 1},
	TextureSpec{"mushroom.png", 1, 1},
};

Game::Game() : seguir(true), map(new Tilemap(MAP_NAME, this))
{
	// Inicializa la SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("First test with SDL",
	                          SDL_WINDOWPOS_CENTERED,
	                          SDL_WINDOWPOS_CENTERED,
	                          WIN_WIDTH,
	                          WIN_HEIGHT,
	                          SDL_WINDOW_SHOWN);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (window == nullptr || renderer == nullptr)
		throw "Error cargando SDL"s;

	// Carga las texturas
	for (int i = 0; i < NUM_TEXTURES; ++i)
		textures[i] = new Texture(renderer,
		                          (textureRoot + textureSpec[i].name).c_str(),
		                          textureSpec[i].numRows, textureSpec[i].numColumns);

	// Crea los objetos del juego
	entities = new Entity[2]{
		Player(this, 100, 100),
		Koopa(this, 300, 300),
	};
}

Game::~Game()
{
	// Elimina los objetos del juego

	// Elimina las texturas
	for (Texture* texture : textures)
		delete texture;

	delete[] entities;

	// Desactiva la SDL
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void
Game::run()
{
	// Bucle principal del juego
	while (seguir) {
		// Marca de tiempo del inicio de la iteración
		uint32_t inicio = SDL_GetTicks();

		update();       // Actualiza el estado de los objetos del juego
		render();       // Dibuja los objetos en la venta
		handleEvents(); // Maneja los eventos de la SDL

		// Tiempo que se ha tardado en ejecutar lo anterior
		uint32_t elapsed = SDL_GetTicks() - inicio;

		// Duerme el resto de la duraci�n del frame
		if (elapsed < FRAME_RATE)
			SDL_Delay(FRAME_RATE - elapsed);
	}
}

void
Game::render() const
{
	SDL_RenderClear(renderer);

	// Pinta los objetos del juego
	//textures[BACKGROUND]->render();
	map->render();
	SDL_RenderPresent(renderer);
}

void
Game::update()
{
	// Actualiza los objetos del juego
}

void
Game::handleEvents()
{
	// Procesamiento de eventos
	SDL_Event evento;

	while (SDL_PollEvent(&evento)) {
		if (evento.type == SDL_QUIT)
			seguir = false;
		else if (evento.type == SDL_KEYDOWN) {
		}
	}
}
