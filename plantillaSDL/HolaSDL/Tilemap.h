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

	Tilemap(const string& mapName);

	void render(const Game& game);
	void update();
	void hit();
};

