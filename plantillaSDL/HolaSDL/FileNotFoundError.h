#pragma once
#include "GameError.h"
using namespace std;

class FileNotFoundError : public GameError
{
	explicit FileNotFoundError(const string& what_arg) : GameError(what_arg) {}
};

