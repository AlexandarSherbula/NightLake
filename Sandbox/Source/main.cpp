#include "Sandbox.hpp"

int main()
{
	aio::AppSpecifications appSpecs;
	appSpecs.windowSpecs.title  = "Alexio Engine";
	appSpecs.windowSpecs.width  = 424;
	appSpecs.windowSpecs.height = 240;
	appSpecs.windowSpecs.isFullScreen = false;
	appSpecs.graphicsAPI = GraphicsAPI::DX11;

	AIO_BEGIN_SESSION("Start", "Start.json");
	Sandbox sandbox(appSpecs);
	AIO_END_SESSION();

	AIO_BEGIN_SESSION("Runtime", "Runtime.json");
	sandbox.Run();
	AIO_END_SESSION();
	return 0;
}