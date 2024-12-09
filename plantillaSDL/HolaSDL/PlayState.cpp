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
#include "PauseState.h"
#include "Shotgun.h"

#include <iostream>
#include <fstream>
using namespace std;

void PlayState::equipPlayer(Weapon* weapon)
{
	gameObjects.push_back(weapon);
	player->setWeapon(weapon);
}

PlayState::PlayState(SDL_App* app, int level) : GameState(app)
{
	this->app = app;
	loadLevel(level);
}

PlayState::~PlayState()
{
	// Elimina los objetos del juego

	 //delete gameObjects
	for (auto it : gameObjects) delete it;

	delete map;
}

Vector2D<float> PlayState::ScreenToWorld(Vector2D<float> position) const
{
	return Vector2D<float>((position.getX() + _mapOffset) / TILE_SIDE, position.getY() / TILE_SIDE);
}

Vector2D<float> PlayState::WorldToScreen(Vector2D<float> position) const
{
	return Vector2D<float>((position.getX() * TILE_SIDE) - _mapOffset, position.getY() * TILE_SIDE);
}

void PlayState::update()
{
	addVisibleObjects();

	GameState::update();

	int maxOffset = map->GetMapWidth() * TILE_SIDE - WIN_WIDTH * 1.5f;
	if ((player->getRenderRect().x) > (SDL_App::WIN_WIDTH / 2))
	{
		_mapOffset = player->getRenderRect().x + _mapOffset - (SDL_App::WIN_WIDTH / 2);

		if (_mapOffset > maxOffset) _mapOffset = maxOffset;
		else if (_mapOffset < _lastOffset) _mapOffset = _lastOffset;

		_lastOffset = _mapOffset;
	}

	if (loadNext) nextLevel();
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
		SceneObject* object = static_cast<SceneObject*>(it);

		SDL_Rect other = object->getCollisionRect();
		collision = object->hit(rect, target);

		if (collision.result != Collision::NONE) return collision;
	}

	return collision;
}

void PlayState::reset()
{
	for (auto it : gameObjects)
	{
		if(it != player && it != map) delete it;
	}

	_mapOffset = _lastOffset = 0;
	player->reset();
	nextObject = 0;
}

void PlayState::loadLevel(int levelIndex)
{
	_mapOffset = _lastOffset = 0;
	string level = std::to_string(levelIndex);

	map = new Tilemap("world" + level + ".csv", this);
	gameObjects.push_back(map);

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
	SDL_SetRenderDrawColor(app->getRenderer(), R, G, B, 0);

	while (entrada) {
		char type;
		entrada >> type;

		float x, y;
		entrada >> x >> y;

		x *= TILE_SIDE;
		y *= TILE_SIDE;

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
				else if (action == 'E') blockAction = ESCOPETA;
				break;
			}

			objectQueue.push_back(new Block(this, x, y, blockType, blockAction));
			break;
		}
	}
}

void PlayState::nextLevel()
{
	for (auto it : gameObjects)
	{
		delete it;
	}

	for (auto it : objectQueue)
	{
		delete it;
	}

	objectQueue.clear();
	nextObject = 0;

	//currentLevel++;

	loadLevel(2);
}

void PlayState::addObject(SceneObject* obj)
{
	gameObjects.push_back(obj);
}

void PlayState::addVisibleObjects()
{
	// Borde derecho del mapa (más una casilla)
	const int rightThreshold = (_mapOffset * SDL_App::TILE_SIDE) + SDL_App::WINDOW_WIDTH + SDL_App::TILE_SIDE;

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