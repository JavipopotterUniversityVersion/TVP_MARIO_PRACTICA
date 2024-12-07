#include "AnimationState.h"
#include "SDL_App.h"

AnimationState::AnimationState(PlayState* game, Callback callback) : GameState(game->getApp()), game(game), callback(callback) {}

void AnimationState::render() const
{
	game->render();
}

void AnimationState::update()
{
	if (callback() == false)
	{
		game->reset();
		getApp()->popState();
	}
}