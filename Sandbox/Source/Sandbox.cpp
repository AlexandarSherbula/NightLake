#include "Sandbox.hpp"

Sandbox::Sandbox()
{
	
}

Sandbox::Sandbox(nle::AppSpecifications& appSpecs)
	: Application (appSpecs)
{
	SetRenderingApi(DX11);
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
	using namespace nle;
	if (Input::GetKeyboard()->IsHeld(KeyCode::F10))
		NLE_LOG_TRACE("F10 was Held");
	
	if (Input::GetKeyboard()->IsReleased(KeyCode::F10))
		NLE_LOG_TRACE("F10 was released"); 
	
	if (Input::GetMouse()->IsHeld(L_BUTTON))
		NLE_LOG_TRACE("Left click was pressed: x: {0}, y: {1}", Input::GetMouse()->X(), Input::GetMouse()->Y());
	
	if (Input::GetMouse()->IsReleased(M_BUTTON))
		NLE_LOG_TRACE("Left click was released.");

	if (Input::GetMouse()->Wheel().y != 0.0f)
		NLE_LOG_TRACE("Wheel: {0}", Input::GetMouse()->Wheel().y);
}

void MainLayer::OnImGuiRender()
{
}

void MainLayer::OnEvent(nle::Event& event)
{
}
