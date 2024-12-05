#include <iostream>

#include "Tilemap.h"
#include "SDL_App.h"
#include "PlayState.h"

using namespace std;
int main(int argc, char* argv[])
{
	try {
		SDL_App* app = new SDL_App();
		app->run();
	}
	catch (const std::string& msg) {
		cerr << "Error: " << msg << endl;
	}

	return 0;
}