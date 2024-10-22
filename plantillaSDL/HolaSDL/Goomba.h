#pragma once
class Entity;
class Game;

class Goomba : public Entity 
{
    public:
        Goomba(Game* game, int x, int y) : Entity(game, x, y) {}
};