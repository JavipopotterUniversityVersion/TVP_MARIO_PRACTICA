#pragma once
#include "GameError.h"
using namespace std;

class FileNotFoundError : public GameError
{
public:
	explicit FileNotFoundError(const string& fileName) : GameError(
		"Error al leer el archivo " + fileName) {}
};

