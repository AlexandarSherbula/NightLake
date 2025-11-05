#include "Sandbox.hpp"

int main()
{
	aio::AppSpecifications appSpecs;
	appSpecs.title  = "Alexio Engine";
	appSpecs.width  = 1280;
	appSpecs.height = 720;
	appSpecs.isFullScreen = false;
	appSpecs.graphicsAPI = GraphicsAPI::DX11;

	Sandbox sandbox(appSpecs);
	sandbox.Run();
	return 0;
}