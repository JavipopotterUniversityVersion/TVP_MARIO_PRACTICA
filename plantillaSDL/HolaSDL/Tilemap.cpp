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
	Vector2D<float> offsets[8] = { Vector2D<float>(0, 0), Vector2D<float>(1, 0), Vector2D<float>(1, 1), Vector2D<float>(0, -1), Vector2D<float>(0, 1), Vector2D<float>(-1, 0),
	Vector2D<float>(0, 2), Vector2D<float>(1, 2) };

	for (int i = 0; i < 8; i++)
	{
		Vector2D<int> tilePos = Vector2D<int>(position.getX() + offsets[i].getX(), position.getY() + offsets[i].getY());

		if (tilePos.getX() >= 0 && tilePos.getX() < map[0].size() && tilePos.getY() >= 0 && tilePos.getY() < map.size()
			&& isTileCollidable(tilePos.getX(), tilePos.getY()))
		{
			SDL_Rect tile;
			Vector2D<float> screenPos = game->WorldToScreen(Vector2D<float>(tilePos.getX(), tilePos.getY()));
			tile.x = screenPos.getX();
			tile.y = screenPos.getY();
			tile.w = Game::TILE_SIZE /*+ 8*/;
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

int TileMap::render() const
{
	vector<vector<int>> indices;  // atributo de TileMap
	Texture* background;  // atributo de TileMap

	constexpr int TILE_SIDE = 32;  // constantes estáticas en Game
	constexpr int WINDOW_WIDTH = 18;
	constexpr int WINDOW_HEIGHT = 16;

	int mapOffset;  // atributo de Game

	// Primera columna de la matriz del mapa visible en la ventana
	int col0 = mapOffset / TILE_SIDE;
	// Anchura oculta de esa primera columna
	int d0 = mapOffset % TILE_SIDE;

	// Recuadro donde se pintará la tesela en la ventana
	SDL_Rect rect;
	rect.w = TILE_SIDE;
	rect.h = TILE_SIDE;

	// Pintamos los WINDOW_WIDTH + 1 (aunque se salga) x WINDOW_HEIGHT recuadros del mapa
	for (int col = 0; col < WINDOW_WIDTH + 1; ++col) {
		rect.x = -d0 + col * TILE_SIDE;

		for (int row = 0; row < WINDOW_HEIGHT; ++row) {
			// Índice en el conjunto de patrones de la matriz de índices
			int indice = indices[row][col0 + col];

			// Si el índice es -1 no se pinta nada
			if (indice != -1) {
				// Separa número de fila y de columna
				int frameCol = indice % texture->getNumColumns();
				int frameRow = indice / texture->getNumColumns();

				rect.y = row * TILE_SIDE;

				// Usa renderFrame para pintar la tesela
				background->renderFrame(rect, frameRow, frameCol);
			}
		}
	}
}

Collision TileMap::hit(const SDL_Rect& rect, bool fromPlayer)
{
	vector<vector<int>> matrix; // atributos de TileMap
	Texture* texture;

	constexpr int OBSTACLE_THRESHOLD = 4; // constante

	// Celda del nivel que contiene la esquina superior izquierda del rectángulo
	int row0 = rec.y / Game::TILE_SIDE;
	int col0 = rec.x / Game::TILE_SIDE;

	// Celda del nivel que contiene la esquina inferior derecha del rectángulo
	int row1 = (rect.y + rect.h - 1) / Game::TILE_SIDE;
	int col1 = (rect.x + rect.w - 1) / Game::TILE_SIDE;

	for (int row = row0; row <= row1; ++row)
		for (int col = col0; col <= col1; ++col) {
			int indice = matriz[row][col];

			if (indice != -1 && indice % texture->getNumColumns() < OBSTACLE_THRESHOLD)
				return true;
		}

	return false;
}