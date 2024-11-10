#pragma once
#include <vector>
#include <iostream>
#include "Vector2D.h"
#include "SDL.h"
class Game;
class Texture;
using namespace std;

class Tilemap
{
	private:
		vector<vector<int>> map;
		Texture* texture;
		const int MAP_HEIGHT = 16;
		Game* game;
		vector<SDL_Rect> getNearestTiles(Vector2D<float> position);
		bool isTileCollidable(int x, int y);

	public:
		Tilemap(const string& mapName, Game* game);

		void render();
		void update();
		bool collides(SDL_Rect& rectToCheck);

		int GetMapWidth() { return map[0].size(); };
};

