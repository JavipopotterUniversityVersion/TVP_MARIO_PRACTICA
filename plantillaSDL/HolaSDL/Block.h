#pragma once
#include "SceneObject.h"
#include "Vector2D.h"
#include "Texture.h"
#include "SDL_App.h"

enum BlockType { SORPRESA = 0, OCULTO, VACIO = 4, LADRILLO = 5};
enum BlockAction { POTENCIADOR, MONEDA };

class Block : public SceneObject
{
	private:
		BlockType type;
		BlockAction action;
		bool active = true;

	public:
		Block(PlayState* game, int x, int y, BlockType type, BlockAction action);
		Block(Block& block) : Block(block.playState, block.position.getX(), block.position.getY(), block.type, block.action) {};
		SceneObject* clone() override;
		void render() const override;
		Collision hit(const SDL_Rect& rect, Collision::Target target) override;
		bool isActive() { return active; }
};