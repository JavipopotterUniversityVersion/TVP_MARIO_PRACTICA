#include "Koopa.h"
#include "Game.h"

Koopa::Koopa(Game* game, int x, int y) : game(game), texture(game->getTexture(Game::KOOPA))
{
    position.Set(x, y);
}

void Koopa::render()
{
    SDL_Rect rect;
    rect.w = 32;
    rect.h = 32;
    rect.x = (position.getX() * Game::TILE_SIDE) - game->GetMapOffset();
    rect.y = position.getY() * Game::TILE_SIDE;
    texture->renderFrame(rect, 0, 0);
}

void Koopa::update()
{
    int newPos = position.getY() + 5;

    position.Set(position.getX(), newPos);
}