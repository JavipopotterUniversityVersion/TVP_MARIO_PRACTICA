#pragma once
//class Entity;
#include "Vector2D.h"
#include "Texture.h"
#include "SceneObject.h"
#include "Collision.h"
class Game;

class Player : public SceneObject
{
	private:
		static constexpr float JUMP_TIME = 0.5f;
		static constexpr float SPEED = 0.35f;
		static constexpr float JUMP_FORCE = 1.5f;
		static constexpr float INMUNE_TIME = 1.5f;

		Vector2D<float> initialPosition;
		bool canJump = false;
		float jumpTimer = JUMP_TIME;
		float inmuneTimer = INMUNE_TIME;
		int vidas;
		bool flipped = false;
		bool superMario = false;

		void SetFrameRange(int x, int y) { frameRange.Set(x, y); }

	public:
		Player(Game* game, int x, int y, int vidas);
		Player(Player& const player) : Player(player.game, player.position.getX(), player.position.getY(), player.vidas) {};
		void handleEvent(SDL_Event& evento);

		void update() override;
		Collision hit(SDL_Rect rect, Collision::Target target) override;
		SceneObject* clone() override;

		void goSuperMario();
};