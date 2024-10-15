#include "Tilemap.h"
#include <fstream>
#include <string>

void Tilemap::render(const Game& game)
{
	
}

Tilemap::Tilemap(const string& mapName)
{
	string path = ".../Assets/imgs" + mapName;

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
		int width = aux.size() / MAP_HEIGHT;

		for (int i = 0; i < MAP_HEIGHT; i++)
		{
			vector<int> row;
			for (int j = 0; j < width; j++) row.push_back(aux[i * width + j]);
			map.push_back(row);
		}
	}
	else
	{
		cout << "Error al abrir el archivo " << mapName << endl;
	}
}