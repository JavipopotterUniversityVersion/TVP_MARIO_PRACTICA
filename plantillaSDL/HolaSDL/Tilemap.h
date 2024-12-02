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

	public:
		Tilemap(const string& mapName, PlayState* game);

		void render() const override;
		Collision hit(const SDL_Rect& region, Collision::Target target) override;
		SceneObject* clone() override { return NULL; };

		int GetMapWidth() { return map[0].size(); };
};

