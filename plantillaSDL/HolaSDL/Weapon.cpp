#include "Weapon.h"
#include "PlayState.h"
#include <iostream>

Weapon::Weapon(PlayState* game, SDL_App::TextureName texture, SceneObject* father = nullptr) : SceneObject(game, 0, 0), father(father)
{
	this->texture = game->getApp()->getTexture(texture);
}

void Weapon::update()
{
	position = father->getPosition();
	position += Vector2D<float>{-SDL_App::TILE_SIDE / 2, 0};
}

Vector2D<float> Weapon::up(int offset)
{
	int trueRot = _rotation + offset;
	Vector2D<float> up{ cosf(trueRot * M_PI / 180), sinf(trueRot * M_PI / 180) };
	if (flip) up = up * -1;

	return up;
}