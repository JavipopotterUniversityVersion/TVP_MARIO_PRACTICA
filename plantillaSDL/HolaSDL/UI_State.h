#pragma once
#include "GameState.h"
#include "Texture.h"
#include "SDL_App.h"
class UI_State : public GameState
{
protected:
	Texture* background;
	Texture* mushroom;

	Vector2D<int> pointerPosition;

	void setPointer(int x, int y) { pointerPosition.Set(x, y); }
public:
	UI_State(SDL_App* app, SDL_App::TextureName backgName);
	void handleEvent(const SDL_Event& event) override;
	void render() const override;
};

