#include "Game.hpp"
#include <iostream>

int main()
{
	nle::AppSpecifications appSpecs;
	appSpecs.title = "NightLake Engine";
	appSpecs.width = 1280;
	appSpecs.height = 720;

	Game game(appSpecs);
	game.Run();
	return 0;
}