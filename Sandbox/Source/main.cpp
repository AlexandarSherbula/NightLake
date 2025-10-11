#include "Sandbox.hpp"

int main()
{
	aio::AppSpecifications appSpecs;
	appSpecs.title = "Alexio Engine";
	appSpecs.width = 1280;
	appSpecs.height = 720;

	Sandbox sandbox(appSpecs);
	sandbox.Run();
	return 0;
}