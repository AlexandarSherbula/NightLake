#include "Sandbox.hpp"


Sandbox::Sandbox()
{
	
}

Sandbox::Sandbox(aio::AppSpecifications& appSpecs)
	: Application (appSpecs)
{
	aio::Renderer::SetAPI(OpenGL);
	PushLayer(new MainLayer());
}

Sandbox::~Sandbox()
{
}

MainLayer::MainLayer()
	: Layer("Main")
{
}

void MainLayer::OnAttach()
{
	
}

void MainLayer::OnUpdate()
{
	using namespace aio;
	if (Input::GetKeyboard()->IsHeld(KeyCode::F10))
		AIO_LOG_TRACE("F10 was Held");
	
	if (Input::GetKeyboard()->IsReleased(KeyCode::F10))
		AIO_LOG_TRACE("F10 was released");
}

void MainLayer::OnImGuiRender()
{
}

void MainLayer::OnEvent(aio::Event& event)
{
}
