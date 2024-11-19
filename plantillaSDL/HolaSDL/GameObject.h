#pragma once
class Game;

class GameObject
{
	private:
		Game* game;
	public:
		void render();
		void update();
};

