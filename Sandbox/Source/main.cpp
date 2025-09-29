#include "Game.hpp"
#include <iostream>

int main()
{
	nle::AppSpecifications appSpecs;
	appSpecs.windowSpecs.title = "NightLake Engine";
	appSpecs.windowSpecs.width = 1280;
	appSpecs.windowSpecs.height = 720;

	Game game(appSpecs);
	game.Run();
	return 0;
}