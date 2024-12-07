#include "Shotgun.h"
#include "Bullet.h"
#include <iostream>

Shotgun::Shotgun(PlayState* game, SceneObject* father) : Weapon(game, SDL_App::SHOTGUN, father)
{
	float relation = 344 / 76;
	_width = 64;
	_height = 64 / relation;
}

void Shotgun::Use()
{
	Vector2D<float> spawnPoint = position + up() * (_width / 2);

	std::cout << up().getX() << " " << up().getY() << std::endl;

	for (int i = 0; i < 5; i++)
	{
		game->addObject(new Bullet(playState, spawnPoint.getX(), spawnPoint.getY(), up(offsets[i])));
	}

	father->addVelocity(up() * -60);
}