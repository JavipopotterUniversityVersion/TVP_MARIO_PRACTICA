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
			int indice = map[j][i + x0];
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