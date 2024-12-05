#pragma once
#include "SceneObject.h"
#include "Vector2D.h"
#include "Texture.h"
#include "Collision.h"
class PlayState;

class Player : public SceneObject
{
	private:
		static constexpr float JUMP_TIME = 0.5f;
		static constexpr float SPEED = 10.0f;
		static constexpr float JUMP_FORCE = 120.0f;
		static constexpr float INMUNE_TIME = 1.5f;

		bool canJump = false;
		float jumpTimer = JUMP_TIME;
		float inmuneTimer = INMUNE_TIME;
		int vidas;
		bool flipped = false;
		bool superMario = false;

		void SetFrameRange(int x, int y) { frameRange.Set(x, y); }

	public:
		Player(PlayState* game, int x, int y, int vidas);
		Player(Player& const player) : Player(player.playState, player.position.getX(), player.position.getY(), player.vidas) {};
		void handleEvent(SDL_Event& evento);

		void update() override;
		SDL_Rect getRenderRect() const override;
		SDL_Rect getCollisionRect() const override;
		Collision hit(const SDL_Rect& region, Collision::Target target) override;
		SceneObject* clone() override;

		void getDmg();

		void goSuperMario();
		bool isSuperMario() const { return superMario == true; }
};