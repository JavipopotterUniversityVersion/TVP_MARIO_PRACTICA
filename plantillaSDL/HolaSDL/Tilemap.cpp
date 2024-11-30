#include "Tilemap.h"
#include <fstream>
#include <string>
#include "Texture.h"
#include "SDL_App.h"
#include "SDLError.h"
#include "FileNotFoundError.h"
#include "FileFormatError.h"

Tilemap::Tilemap(const string& mapName, SDL_App* game) : game(game)
{
	string path = "../Assets/maps/" + mapName;

	texture = game->getTexture(SDL_App::BACKGROUND);

	ifstream entrada(path);
	if (!entrada.is_open()) throw new exception("Error leyendo archivo");
	try
	{
		while (entrada) {
			char cAux = ',';
			int c = 0;
			vector<int> aux;
			while (cAux == ',') {
				entrada >> c;
				if (c < -1 || c > 62) throw FileFormatError(path, map.size());
				aux.push_back(c);
				cAux = entrada.get();
				
			}
			map.push_back(aux);
		}
	}
	catch (const FileFormatError &e)
	{
		cout << e.what() << endl;
	}
}

void Tilemap::render() const
{
	int mapOffset = game->getMapOffset();

	// Primera columna de la matriz del mapa visible en la ventana
	int col0 = mapOffset / SDL_App::TILE_SIDE;
	// Anchura oculta de esa primera columna
	int d0 = mapOffset % SDL_App::TILE_SIDE;

	// Recuadro donde se pintará la tesela en la ventana
	SDL_Rect rect;
	rect.w = SDL_App::TILE_SIDE;
	rect.h = SDL_App::TILE_SIDE;

	// Pintamos los WINDOW_WIDTH + 1 (aunque se salga) x WINDOW_HEIGHT recuadros del mapa
	for (int col = 0; col < SDL_App::WINDOW_WIDTH + 1; ++col) {
		rect.x = -d0 + col * SDL_App::TILE_SIDE;

		for (int row = 0; row < SDL_App::WINDOW_HEIGHT; ++row) {
			// Índice en el conjunto de patrones de la matriz de índices
			int temp = col0 + col;

			if (row >= map.size()) row = map.size() - 1;
			if (row < 0) row = 0;
			if (temp >= map[0].size()) temp = map[0].size() - 1;
			if (temp < 0) temp = 0;

			int indice = map[row][temp];

			// Si el índice es -1 no se pinta nada
			if (indice != -1) {
				// Separa número de fila y de columna
				int frameCol = indice % texture->getNumColumns();
				int frameRow = indice / texture->getNumColumns();

				rect.y = row * SDL_App::TILE_SIDE;

				// Usa renderFrame para pintar la tesela
				texture->renderFrame(rect, frameRow, frameCol);
			}
		}
	}
}

Collision Tilemap::hit(const SDL_Rect& rect)
{
	Collision collision;

	constexpr int OBSTACLE_THRESHOLD = 4; // constante

	// Celda del nivel que contiene la esquina superior izquierda del rectángulo
	int row0 = rect.y / SDL_App::TILE_SIDE;
	int col0 = rect.x / SDL_App::TILE_SIDE;

	// Celda del nivel que contiene la esquina inferior derecha del rectángulo
	int row1 = (rect.y + rect.h - 1) / SDL_App::TILE_SIDE;
	int col1 = (rect.x + rect.w - 1) / SDL_App::TILE_SIDE;

	for (int row = row0; row <= row1; ++row)
	{
		for (int col = col0; col <= col1; ++col) {

			if (row >= map.size())
			{
				row = map.size() - 1;
				return collision;
			}
			if (row < 0) {
				row = 0;
				return collision;
			}
			if (col >= map[0].size())
			{
				col = map[0].size() - 1;
				return collision;
			}
			if (col < 0) {
				col = 0;
				return collision;
			}

			int indice = map[row][col];

			if (indice == 43) game->setLoadFlag();
			if (indice != -1 && indice % texture->getNumColumns() < OBSTACLE_THRESHOLD)
			{
				SDL_Rect obstacleRect;
				collision.result = collision.OBSTACLE;

				Vector2D<float> pos(col, row);
				obstacleRect.x = pos.getX();
				obstacleRect.y = pos.getY();
				obstacleRect.w = SDL_App::TILE_SIDE;
				obstacleRect.h = SDL_App::TILE_SIDE;

				SDL_Rect intersection;
				SDL_IntersectRect(&rect, &obstacleRect, &intersection);

				collision.horizontal = intersection.w;
				collision.vertical = intersection.h;

				return collision;
			}
		}
	}

	return collision;
}