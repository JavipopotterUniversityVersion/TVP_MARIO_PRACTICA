#include "PlayState.h"

#include <string>

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

PlayState::~PlayState()
{
	// Elimina los objetos del juego

	 //delete gameObjects
	for (auto it : gameObjects) delete it;

	delete map;
}

void
PlayState::run()
{
	// Bucle principal del juego
	while (seguir) {
		// Marca de tiempo del inicio de la iteración
		uint32_t inicio = SDL_GetTicks();

		if (loadNext)
		{
			loadNext = false;
			nextLevel();
		}

		if (resetBool)
		{
			resetBool = false;
			reset();
		}

		update();       // Actualiza el estado de los objetos del juego
		render();       // Dibuja los objetos en la venta
		handleEvent(); // Maneja los eventos de la SDL

		// Tiempo que se ha tardado en ejecutar lo anterior
		uint32_t elapsed = SDL_GetTicks() - inicio;

		// Duerme el resto de la duraci�n del frame
		if (elapsed < FRAME_RATE)
			SDL_Delay(FRAME_RATE - elapsed);
	}
}

Vector2D<float> PlayState::ScreenToWorld(Vector2D<float> position) const
{
	return Vector2D<float>((position.getX() + mapOffset) / TILE_SIDE, position.getY() / TILE_SIDE);
}

Vector2D<float> PlayState::WorldToScreen(Vector2D<float> position) const
{
	return Vector2D<float>((position.getX() * TILE_SIDE) - mapOffset, position.getY() * TILE_SIDE);
}

void PlayState::render() const
{
	SDL_RenderClear(app->getRenderer());
	map->render();

	for (auto it : gameObjects)
	{
		it->render();
	}

	SDL_RenderPresent(app->getRenderer());
}

void
PlayState::update()
{
	addVisibleObjects();

	for (auto it : gameObjects)
	{
		it->update();
	}

	int maxOffset = map->GetMapWidth() * TILE_SIDE - WIN_WIDTH * 1.5f;
	if ((player->getRenderRect().x) > (SDL_App::WIN_WIDTH / 2))
	{
		mapOffset = player->getRenderRect().x + mapOffset - (SDL_App::WIN_WIDTH / 2);
		if (mapOffset > maxOffset) mapOffset = maxOffset;
	}
}

void
PlayState::handleEvent(const SDL_Event& event)
{
	SDL_Event evento = event;

	while (SDL_PollEvent(&evento)) {
		if (evento.type == SDL_QUIT) seguir = false;
		else
		{
			player->handleEvent(evento);
		}
	}
}

Collision PlayState::checkCollision(SDL_Rect& rect, Collision::Target target)
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

	Collision mapCol = map->hit(rect);
	if (mapCol.result != Collision::NONE) collision = mapCol;

	return collision;
}

void PlayState::reset()
{
	for (auto it : gameObjects) delete it;
	delete map;

	objectQueue.clear();
	nextObject = 0;

	loadLevel(currentLevel);
}

void PlayState::loadLevel(int levelIndex)
{
	mapOffset = 0;
	string level = std::to_string(levelIndex);

	map = new Tilemap("world" + level + ".csv", this);

	string path = "../Assets/maps/world" + level + ".txt";

	ifstream entrada(path);
	try
	{
		if (!entrada.is_open()) throw FileNotFoundError(path);
	}
	catch (const FileNotFoundError& e)
	{
		cout << e.what() << endl;
	}

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
			Goomba* aux = new Goomba(this, x, y, true);
			objectQueue.push_back(aux);
			break;
		}
		case 'G':
		{
			Goomba* aux = new Goomba(this, x, y, false);
			objectQueue.push_back(aux);
			break;
		}
		case 'L':
		{
			int speed;
			entrada >> speed;
			Lift* aux = new Lift(this, x, y, speed);
			objectQueue.push_back(aux);
			break;
		}
		case 'B':
			char type, action;
			entrada >> type;

			BlockType blockType;
			BlockAction blockAction = POTENCIADOR;

			switch (type)
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

			objectQueue.push_back(new Block(this, x, y, blockType, blockAction));
			break;
		}
	}
}

void PlayState::nextLevel()
{
	for (auto it : gameObjects) delete it;
	delete map;

	objectQueue.clear();
	nextObject = 0;

	currentLevel++;

	loadLevel(currentLevel);
}

void PlayState::addObject(SceneObject* obj)
{
	gameObjects.push_back(obj);
}

void PlayState::addVisibleObjects()
{
	// Borde derecho del mapa (m�s una casilla)
	const int rightThreshold = mapOffset + Game::WINDOW_WIDTH + Game::TILE_SIDE;

	while (nextObject < objectQueue.size() && objectQueue[nextObject]->getPosition().getX() < rightThreshold)
	{
		addObject(objectQueue[nextObject++]->clone());
	}
}

void PlayState::goSuperMario()
{
	player->goSuperMario();
}

bool PlayState::isSuperMario()
{
	return player->isSuperMario();
}