#pragma once
#include <vector>
#include <iostream>
#include "Vector2D.h"
#include "SDL.h"
#include "Collision.h"
#include "Texture.h"
class Game;
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

		void render() const;
		Collision hit(const SDL_Rect& rect);

		int GetMapWidth() { return map[0].size(); };
};

