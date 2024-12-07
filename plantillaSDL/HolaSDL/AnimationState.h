#pragma once
#include "GameState.h"
#include "PlayState.h"
#include <functional>

using Callback = std::function<bool()>;

class AnimationState : public GameState
{
	PlayState* game;
	Callback callback;
public:
	AnimationState(PlayState* game, Callback callback);
	void render() const override;
	void update() override;
};