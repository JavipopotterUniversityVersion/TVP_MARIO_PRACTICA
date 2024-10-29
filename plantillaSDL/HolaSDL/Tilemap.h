#pragma once
#include <vector>
#include <iostream>
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

	public:
		Tilemap(const string& mapName, Game* game);

		void render();
		void update();
		void hit();

		int GetMapWidth() { return map[0].size(); };
};

