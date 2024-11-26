#pragma once
#include <stdexcept>
using namespace std;

class GameError : public logic_error
{
	//Utiliza los constructores y el método what() heredados de "logic_error"
	using std::logic_error::logic_error;
};

