#pragma once
#include "GameError.h"
using namespace std;

class SDLError : public GameError
{
public:
	explicit SDLError(const string& mensajeEspecificoDeError): GameError("Error de la SDL: "
		+ mensajeEspecificoDeError) {}
};

