#include "Sandbox.hpp"

int main()
{
	nle::AppSpecifications appSpecs;
	appSpecs.title = "NightLake Engine";
	appSpecs.width = 1280;
	appSpecs.height = 720;

	Sandbox sandbox(appSpecs);
	sandbox.Run();
	return 0;
}