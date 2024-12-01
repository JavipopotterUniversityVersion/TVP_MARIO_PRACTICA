#pragma once
#include <vector>
#include <iostream>
#include "Vector2D.h"
#include "SDL.h"
#include "Collision.h"
#include "Texture.h"
#include "SceneObject.h"
using namespace std;

class Tilemap : public SceneObject
{
	private:
		vector<vector<int>> map;
		Texture* texture;
		const int MAP_HEIGHT = 16;
		SDL_App* game;

	public:
		Tilemap(const string& mapName, SDL_App* game);

		void render() const override;
		Collision hit(const SDL_Rect& rect);

		int GetMapWidth() { return map[0].size(); };
};

