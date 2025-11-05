#include "Sandbox.hpp"

int main()
{
	aio::AppSpecifications appSpecs;
	appSpecs.windowSpecs.title  = "Alexio Engine";
	appSpecs.windowSpecs.width  = 424;
	appSpecs.windowSpecs.height = 240;
	appSpecs.windowSpecs.isFullScreen = false;
	appSpecs.graphicsAPI = GraphicsAPI::DX11;

	Sandbox sandbox(appSpecs);
	sandbox.Run();
	return 0;
}