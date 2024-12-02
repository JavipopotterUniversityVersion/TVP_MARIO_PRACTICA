#pragma once
class GameState;

class GameObject
{ 
	protected:
		GameState* game;
	public:
		GameObject(GameState* game) : game(game) {};
		virtual void render() const = 0;
		virtual void update() = 0;
};

