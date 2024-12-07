#include "WeaponPickable.h"
#include "PlayState.h"

WeaponPickable::WeaponPickable(PlayState* game, int x, int y, Weapon* weapon) : Pickable(game, x, y), weapon(weapon)
{
	float relation = 344 / 76;
	_width = 64;
	_height = 64 / relation;

	texture = game->getApp()->getTexture(SDL_App::SHOTGUN);
}

void WeaponPickable::triggerAction()
{
	playState->equipPlayer(weapon);
}