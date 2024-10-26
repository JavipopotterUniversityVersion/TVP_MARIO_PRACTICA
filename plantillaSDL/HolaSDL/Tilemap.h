#pragma once
#include <vector>
#include <iostream>
#include "Game.h"
#include "Texture.h"
using namespace std;

class Tilemap
{
	private:
		vector<vector<int>> map;
		Texture* texture;
		const int MAP_HEIGHT = 16;
		Game* game;

	public:
		Tilemap(const string& mapName, Game* game);

		void render();
		void update();
		void hit();
};

