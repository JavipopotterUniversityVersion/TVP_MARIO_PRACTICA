#pragma once
class Game;

class GameObject
{
	protected:
		Game* game;
	public:
		virtual void render() = 0;
		virtual void update() = 0;
};

