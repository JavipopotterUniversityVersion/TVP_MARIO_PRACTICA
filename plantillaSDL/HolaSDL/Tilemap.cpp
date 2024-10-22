#include "Tilemap.h"
#include <fstream>
#include <string>

void Tilemap::render(const Game& game)
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int c = 0; i < mapWidth; i++)
		{
			//texture->render();
		}
	}
}

Tilemap::Tilemap(const string& mapName, Texture* tex)
{
	string path = ".../Assets/imgs" + mapName;
	texture = tex;
	mapWidth = 0;

	ifstream file(path);
	if (file.is_open())
	{
		vector<int> aux;

		while (!file.eof())
		{
			string line;
			getline(file, line, ',');
			aux.push_back(stoi(line));
		}

		file.close();
		mapWidth = aux.size() / MAP_HEIGHT;

		for (int i = 0; i < MAP_HEIGHT; i++)
		{
			vector<int> row;
			for (int j = 0; j < mapWidth; j++) row.push_back(aux[i * mapWidth + j]);
			map.push_back(row);
		}
	}
	else
	{
		cout << "Error al abrir el archivo " << mapName << endl;
	}
}