#include "Koopa.h"
#include "Game.h"

Koopa::Koopa(SDL_App* game, int x, int y) : game(game), texture(game->getTexture(SDL_App::KOOPA))
{
    position.Set(x, y);
}

void Koopa::render()
{
    SDL_Rect rect;
    rect.w = 32;
    rect.h = 32;
    rect.x = (position.getX() * SDL_App::TILE_SIDE) - game->getMapOffset();
    rect.y = position.getY() * SDL_App::TILE_SIDE;
    texture->renderFrame(rect, 0, 0);
}

void Koopa::update()
{
    int newPos = position.getY() + 5;

    position.Set(position.getX(), newPos);
}