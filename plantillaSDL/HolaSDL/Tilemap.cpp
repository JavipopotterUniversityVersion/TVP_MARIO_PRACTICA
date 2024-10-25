#include "Tilemap.h"
#include <fstream>
#include <string>

void Tilemap::render()
{
	int mapOffset = game->getMapOffset();

	// Primera columna de la matriz del mapa visible en la ventana
	int x0 = mapOffset / Game::TILE_SIZE;
	// Anchura oculta de esa primera columna
	int d0 = mapOffset % Game::TILE_SIZE;

	// Recuadro donde se pintar� la tesela en la ventana
	SDL_Rect rect;
	rect.w = Game::TILE_SIZE;
	rect.h = Game::TILE_SIZE;

	// Pintamos los WINDOW_WIDTH + 1 (aunque se salga) x WINDOW_HEIGHT recuadros del mapa
	for (int i = 0; i < Game::WIN_WIDTH + 2; ++i) {
		for (int j = 0; j < Game::WIN_HEIGHT; ++j) {
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
				//background->renderFrame(rect, fy, fx);
				texture->renderFrame(rect, fy, fx);
			}

		}
	}
}

Tilemap::Tilemap(const string& mapName, Game* game) : game(game), texture(game->getTexture(Game::BLOCKS))
{
	string path = ".../Assets/imgs" + mapName;

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