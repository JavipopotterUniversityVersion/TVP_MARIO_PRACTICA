#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include <SDL.h>
#include <iostream>
#include "Collision.h"
#include "Texture.h"
class PlayState;

class SceneObject : public GameObject
{
	protected:
		Vector2D<float> size;
		Vector2D<float> velocity;
		PlayState* playState;

		const float SPEED_LIMIT = 1.5f;
		const float MOVE_PERIOD = 1;

		int _width = 32;
		int _height = 32;
		SDL_RendererFlip flip = SDL_FLIP_NONE;

		int _rotation = 0;

		Texture* texture;
		Vector2D<int> frameRange;
		int currentFrame = 0;

		void sumToCurrentFrame()
		{
			currentFrame++;
			if (currentFrame > frameRange.getY() || currentFrame < frameRange.getX()) currentFrame = frameRange.getX();
		}
		int getCurrentFram() { return currentFrame; }

		float moveDelay = 0.5f;
		bool active = true;
	public:
		virtual Collision hit(const SDL_Rect& region, Collision::Target target) = 0;
		SceneObject(PlayState* app, int x, int y);
		SceneObject(const SceneObject* obj) : SceneObject(obj->playState, obj->position.getX(), obj->position.getY()) {};

		Collision tryToMove(const Vector2D<float>& speed, Collision::Target target);
		virtual SDL_Rect getRenderRect() const;
		virtual SDL_Rect getCollisionRect() const;

		virtual SceneObject* clone() = 0;
		Vector2D<float> getPosition() { return position; }
		void setRotation(int rot) { _rotation = rot; }

		void update() override;
		void render() const override;
		void addVelocity(Vector2D<float> vel) { velocity += vel; }

		void setFlip(SDL_RendererFlip newFlip) { flip = newFlip; }
};

