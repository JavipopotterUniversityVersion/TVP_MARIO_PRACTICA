#include <string>

#include "Game.h"
#include "Entity.h"
#include "Player.h"
#include "Goomba.h"
#include "Tilemap.h"
#include "Block.h"
#include "Collision.h"
#include "SceneObject.h"

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
const array<TextureSpec, Game::NUM_TEXTURES> textureSpec{
	TextureSpec{"background.png", 9, 7},
	TextureSpec{"mario.png", 12, 1},
	TextureSpec{"supermario.png", 22, 1},
	TextureSpec{"blocks.png", 6, 1},
	TextureSpec{"goomba.png", 3, 1},
	TextureSpec{"koopa.png", 4, 1},
	TextureSpec{"mushroom.png", 1, 1},
};

Game::Game() : seguir(true)
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
	{
		textures[i] = new Texture(renderer,
			(textureRoot + textureSpec[i].name).c_str(),
			textureSpec[i].numRows, textureSpec[i].numColumns);
	}

	// Crea los objetos del juego
	/*entities = new Entity[2]{
		Player(this, 100, 100),
		Koopa(this, 300, 300),
	};*/

	map = new Tilemap("world1.csv", this);

	string path = "../Assets/maps/world1.txt";

	ifstream entrada(path);
	if (!entrada.is_open()) throw new exception("Error leyendo archivo");

	int R, G, B;
	entrada >> R >> G >> B;
	SDL_SetRenderDrawColor(renderer, R, G, B, 0);

	while (entrada) {
		char type;
		entrada >> type;

		float x, y;
		entrada >> x >> y;

		switch (type)
		{
			case 'M':
				int vidas;
				entrada >> vidas;

				player = new Player(this, x, y, vidas);
				gameObjects.push_back(player);
				break;
			case 'K':
			{
				Goomba* aux = new Goomba(this, x, y);
				gameObjects.push_back(aux);
				break;
			}
			case 'G':
			{
				Goomba* aux = new Goomba(this, x, y);
				gameObjects.push_back(aux);
				break;
			}
			case 'B':
				char type, action;
				entrada >> type;

				BlockType blockType;
				BlockAction blockAction = POTENCIADOR;

				switch(type)
				{
					case 'B':
						blockType = LADRILLO;
						break;
					case '0':
						blockType = VACIO;
						break;
					case 'H':
						blockType = OCULTO;
						entrada >> action;

						if (action == 'C') blockAction = MONEDA;
						break;
					case '?':
						entrada >> action;
						blockType = SORPRESA;

						if (action == 'C') blockAction = MONEDA;
						break;
				}

				gameObjects.push_back(new Block(this, x, y, blockType, blockAction));
				break;
		}
	}
}

Game::~Game()
{
	// Elimina los objetos del juego

	// Elimina las texturas
	for (Texture* texture : textures)
		delete texture;

	//delete gameObjects

	delete map;

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

Vector2D<float> Game::ScreenToWorld(Vector2D<float> position) const
{
	return Vector2D<float>((position.getX() + mapOffset) / TILE_SIDE, position.getY() / TILE_SIDE);
}

Vector2D<float> Game::WorldToScreen(Vector2D<float> position) const
{
	return Vector2D<float>((position.getX() * TILE_SIDE) - mapOffset, position.getY() * TILE_SIDE);
}

void
Game::render()
{
	SDL_RenderClear(renderer);
	map->render();

	for (auto it : gameObjects)
	{
		it->render();
	}

	SDL_RenderPresent(renderer);
}

void
Game::update()
{
	for (auto it : gameObjects)
	{
		it->update();
	}

	int maxOffset = map->GetMapWidth() * TILE_SIDE - WIN_WIDTH * 1.5f;
	if ((player->getCollisionRect().x - mapOffset) > (Game::WIN_WIDTH / 2))
	{
		mapOffset = player->getCollisionRect().x - (Game::WIN_WIDTH / 2);
		if (mapOffset > maxOffset) mapOffset = maxOffset;
	}
}

void
Game::handleEvents()
{
	// Procesamiento de eventos
	SDL_Event evento;

	while (SDL_PollEvent(&evento)) {
		if (evento.type == SDL_QUIT) seguir = false;
		else
		{
			player->handleEvent(evento);
		}
	}
}

Collision Game::checkCollision(SDL_Rect& rect, Collision::Target target)
{
	Collision collision;

	for (auto it : gameObjects)
	{
		SDL_Rect other = it->getCollisionRect();
		if (SDL_HasIntersection(&rect, &other))
		{
			collision = it->hit(rect, target);
		}
	}

	map->hit(rect);
	return collision;
}

void Game::reset()
{
	mapOffset = 0;
}