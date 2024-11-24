#include "Tilemap.h"
#include <fstream>
#include <string>
#include "Texture.h"
#include "Game.h"

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

void Tilemap::render() const
{
	int mapOffset = game->GetMapOffset();

	// Primera columna de la matriz del mapa visible en la ventana
	int col0 = mapOffset / Game::TILE_SIDE;
	// Anchura oculta de esa primera columna
	int d0 = mapOffset % Game::TILE_SIDE;

	// Recuadro donde se pintará la tesela en la ventana
	SDL_Rect rect;
	rect.w = Game::TILE_SIDE;
	rect.h = Game::TILE_SIDE;

	// Pintamos los WINDOW_WIDTH + 1 (aunque se salga) x WINDOW_HEIGHT recuadros del mapa
	for (int col = 0; col < Game::WINDOW_WIDTH + 1; ++col) {
		rect.x = -d0 + col * Game::TILE_SIDE;

		for (int row = 0; row < Game::WINDOW_HEIGHT; ++row) {
			// Índice en el conjunto de patrones de la matriz de índices
			int indice = map[row][col0 + col];

			// Si el índice es -1 no se pinta nada
			if (indice != -1) {
				// Separa número de fila y de columna
				int frameCol = indice % texture->getNumColumns();
				int frameRow = indice / texture->getNumColumns();

				rect.y = row * Game::TILE_SIDE;

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
	int row0 = rect.y / Game::TILE_SIDE;
	int col0 = rect.x / Game::TILE_SIDE;

	// Celda del nivel que contiene la esquina inferior derecha del rectángulo
	int row1 = (rect.y + rect.h - 1) / Game::TILE_SIDE;
	int col1 = (rect.x + rect.w - 1) / Game::TILE_SIDE;

	for (int row = row0; row <= row1; ++row)
	{
		for (int col = col0; col <= col1; ++col) {
			int indice = map[row][col];

			if (indice != -1 && indice % texture->getNumColumns() < OBSTACLE_THRESHOLD)
			{
				collision.result = Collision::OBSTACLE;
				return collision;
			}
		}
	}

	return collision;
}