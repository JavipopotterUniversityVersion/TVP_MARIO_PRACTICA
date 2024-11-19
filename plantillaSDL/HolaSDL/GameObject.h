#pragma once
class Game;

class GameObject
{
	protected:
		Game* game;
	public:
		virtual void render();
		virtual void update();
};

