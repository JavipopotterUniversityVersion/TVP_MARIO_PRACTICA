#include <iostream>

#include "Tilemap.h"
#include "SDL_App.h"
#include "GameState.h"

using namespace std;
int main(int argc, char* argv[])
{
	try {
		SDL_App game;
		game.run();
	}
	catch (const std::string& msg) {
		cerr << "Error: " << msg << endl;
	}

	return 0;
}