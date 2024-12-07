#pragma once
#include "SceneObject.h"
#include "SDL_App.h"
class Weapon : public SceneObject
{
protected:
	SceneObject* father;
public:
	Weapon(PlayState* game, SDL_App::TextureName texture, SceneObject* father);
	virtual void Use() = 0;
	void update() override;

	Vector2D<float> up(int offset = 0);

	void setFather(SceneObject* newFather) { father = newFather; }
	Collision hit(const SDL_Rect& region, Collision::Target target) override { return Collision{}; };
	SceneObject* clone() override { return this; }
};