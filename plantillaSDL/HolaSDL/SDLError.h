#pragma once
#include "GameError.h"
using namespace std;

class SDLError : public GameError
{
public:
	explicit SDLError(const string& what_arg): GameError(what_arg) {}
};

