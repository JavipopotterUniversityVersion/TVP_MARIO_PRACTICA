#pragma once
#include "GameError.h"
#include <iostream>
#include <string>
using namespace std;

class FileFormatError : public GameError
{
public:
	explicit FileFormatError(const string& fileName, int line) : GameError("Error al leer el archivo "
		+ fileName + " en la línea " + std::to_string(line)) {}
};

