#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include "Game.h"

enum BlockType { SORPRESA = 0, OCULTO, VACIO = 4, LADRILLO = 5};
enum BlockAction { POTENCIADOR, MONEDA };

class Block : public SceneObject
{
	private:
		BlockType type;
		BlockAction action;
		bool active = true;

	public:
		Block(Game* game, int x, int y, BlockType type, BlockAction action) : SceneObject(game, x, y), type(type), action(action) { texture = game->getTexture(Game::BLOCKS); };
		void render() override;
		Collision hit(SDL_Rect rect, Collision::Target target) override;
		bool isActive() { return active; }
};