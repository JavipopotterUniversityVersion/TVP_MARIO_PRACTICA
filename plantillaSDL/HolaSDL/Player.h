#pragma once
#include "SceneObject.h"
#include "Vector2D.h"
#include "Texture.h"
#include "Collision.h"
#include "Weapon.h"
class PlayState;

class Player : public SceneObject
{
	private:
		static constexpr float JUMP_TIME = 0.5f;
		static constexpr float SPEED = 15.0f;
		static constexpr float JUMP_FORCE = 120.0f;
		static constexpr float INMUNE_TIME = 1.5f;

		bool canJump = false;
		float jumpTimer = JUMP_TIME;
		float inmuneTimer = INMUNE_TIME;
		int vidas;
		bool flipped = false;
		bool superMario = false;

		bool _visible = true;
		bool isVisible() const { return _visible; }

		Vector2D<float> initialPos;

		void SetFrameRange(int x, int y) { frameRange.Set(x, y); }
		Weapon* _currentWeapon;

	public:
		Player(PlayState* game, int x, int y, int vidas);
		Player(Player& const player) : Player(player.playState, player.position.getX(), player.position.getY(), player.vidas) {};
		void handleEvent(SDL_Event& evento);

		void update() override;
		void render() const const;
		SDL_Rect getRenderRect() const override;
		SDL_Rect getCollisionRect() const override;
		Collision hit(const SDL_Rect& region, Collision::Target target) override;
		SceneObject* clone() override;
		bool deathAnimation();

		void setWeapon(Weapon* weapon)
		{
			if (_currentWeapon != nullptr) delete _currentWeapon;
			_currentWeapon = weapon;
			_currentWeapon->setFather(this);
		}

		void getDmg();
		void reset() { position.Set(initialPos.getX(), initialPos.getY()); _currentWeapon = nullptr; }

		void goSuperMario();
		bool isSuperMario() const { return superMario == true; }
};