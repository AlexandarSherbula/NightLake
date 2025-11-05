#include "Sandbox.hpp"

int main()
{
	aio::Renderer::SetAPI(DX11);

	aio::AppSpecifications appSpecs;
	appSpecs.title  = "Alexio Engine";
	appSpecs.width  = 1280;
	appSpecs.height = 720;
	appSpecs.isFullScreen = false;

	Sandbox sandbox(appSpecs);
	sandbox.Run();
	return 0;
}