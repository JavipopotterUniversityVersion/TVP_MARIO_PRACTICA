#include "Tilemap.h"
#include <fstream>
#include <string>

#include "Game.h"

void Tilemap::render()
{
	int mapOffset = game->GetMapOffset();

	// Primera columna de la matriz del mapa visible en la ventana
	int x0 = mapOffset / Game::TILE_SIZE;
	// Anchura oculta de esa primera columna
	int d0 = mapOffset % Game::TILE_SIZE;

	// Recuadro donde se pintar� la tesela en la ventana
	SDL_Rect rect;
	rect.w = Game::TILE_SIZE;
	rect.h = Game::TILE_SIZE;

	// Pintamos los WINDOW_WIDTH + 1 (aunque se salga) x WINDOW_HEIGHT recuadros del mapa
	for (int i = 0; i < Game::WINDOW_WIDTH ; ++i) {
		for (int j = 0; j < Game::WINDOW_HEIGHT ; ++j) {
			// �ndice en el conjunto de patrones de la matriz de �ndices
			//int indice = indices[x0 + i][j];
			int indice = -1;

			if (j >= 0 && i >= 0 && j < map.size() && i < map[j].size()) indice = map[j][i + x0];

			if (indice != -1) {
				// Separa n�mero de fila y de columna
				int fx = indice % 9;
				int fy = indice / 9;

				rect.x = -d0 + i * Game::TILE_SIZE;
				rect.y = j * Game::TILE_SIZE;

				// Usa renderFrame para pintar la tesela
				texture->renderFrame(rect, fy, fx);
			}

		}
	}
}

Tilemap::Tilemap(const string& mapName, Game* game) : game(game)
{
	string path = "../Assets/maps/" + mapName;

	texture = game->getTexture(Game::BACKGROUND);

	ifstream entrada(path);
	if (!entrada.is_open()) throw new exception("Error leyendo archivo");
	while (entrada) {
		char cAux = ',';
		int c = 0;
		vector<int> aux;
		while (cAux == ',') {
			entrada >> c;
			aux.push_back(c);
			cAux = entrada.get();
		}
		map.push_back(aux);
	}
}

bool Tilemap::isTileCollidable(int x, int y)
{
	int tile = map[y][x];
	tile = tile % 9;
	return tile < 4 && tile != -1;
}

//Nos llega una posición en el mundo y nos devuelve las teselas que la rodean
vector<SDL_Rect> Tilemap::getNearestTiles(Vector2D<float> position)
{
	vector<SDL_Rect> tiles;
	Vector2D<int> offsets[4] = { Vector2D<int>(-1, 0), Vector2D<int>(1, 0), Vector2D<int>(0, -1), Vector2D<int>(0, 1) };

	for (int i = 0; i < 5; i++)
	{
		Vector2D<int> tilePos = Vector2D<int>(position.getX() + offsets[i].getX(), position.getY() + offsets[i].getY());

		if (tilePos.getX() >= 0 && tilePos.getX() < map[0].size() && tilePos.getY() >= 0 && tilePos.getY() < map.size()
			&& isTileCollidable(tilePos.getX(), tilePos.getY()))
		{
			SDL_Rect tile;
			Vector2D<float> screenPos = game->WorldToScreen(Vector2D<float>(tilePos.getX(), tilePos.getY()));
			tile.x = screenPos.getX();
			tile.y = screenPos.getY();
			tile.w = Game::TILE_SIZE;
			tile.h = Game::TILE_SIZE;
			tiles.push_back(tile);
		}
	}

	return tiles;
}

bool Tilemap::collides(SDL_Rect& rectToCheck)
{
	bool collision = false;
	
	Vector2D<float> worldPos = game->ScreenToWorld(Vector2D<float>(rectToCheck.x, rectToCheck.y));
	vector<SDL_Rect> tiles = getNearestTiles(worldPos);

	int i = 0;
	while (i < tiles.size() && !collision)
	{
		if (SDL_HasIntersection(&rectToCheck, &tiles[i]))
		{
			collision = true;
		}
		i++;
	}

	return collision;
}