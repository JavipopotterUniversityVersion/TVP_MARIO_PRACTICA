#pragma once
#include "UI_State.h"
#include "Texture.h"
class EndState : public UI_State
{
	Texture* gameOverTexture;
public:
	EndState(SDL_App* app);
	void render() const override;
};

