#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include "Enemy.h"
#include "Collision.h"

class Goomba : public Enemy
{
	private:
		static constexpr float SPEED = 0.05f;
		bool active = true;
		int currentFrame = 0;
		Vector2D<int> frameRange;
		bool isKoopa;

	public:
		bool isActive() { return active; }
		Goomba(PlayState* game, int x, int y, bool isKoopa);
		Goomba(Goomba& obj) : Goomba(obj.playState, obj.position.getX(), obj.position.getY(), obj.isKoopa) {};
		SceneObject* clone() override;
};