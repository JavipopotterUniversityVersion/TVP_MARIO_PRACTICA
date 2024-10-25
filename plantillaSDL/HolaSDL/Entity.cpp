#include "Entity.h"
void Entity::render()
{

}

void Entity::update()
{

}

void Entity::hit()
{

}

Entity::Entity(Game* game, int x, int y) : game(game)
{
	position.Set(x, y);
}