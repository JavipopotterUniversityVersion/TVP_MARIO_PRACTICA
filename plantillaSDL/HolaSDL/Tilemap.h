#pragma once
#include <vector>
#include <iostream>
#include "Game.h"
#include "Texture.h"
using namespace std;

class Tilemap
{
	vector<vector<int>> map;
	Texture* texture;
	const int MAP_HEIGHT = 16;
	int mapWidth;

	Tilemap(const string& mapName, Texture* tex);

	void render(const Game& game);
	void update();
	void hit();
};

