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
	
	if (Input::GetMouse()->IsReleased(L_BUTTON))
		NLE_LOG_TRACE("Left click was released.");

	if (Input::GetMouse()->WheelY() != 0.0f)
		NLE_LOG_TRACE("Wheel: {0}", Input::GetMouse()->WheelY());
	
	//NLE_LOG_TRACE("LeftStick x: {0}, y: {1}", Input::GetGamepad()->LeftThumbStick().x, Input::GetGamepad()->LeftThumbStick().y);
	//NLE_LOG_TRACE("LeftTrigger: {0}, RightTrigger: {1}", Input::GetGamepad()->LeftTrigger(), Input::GetGamepad()->RightTrigger());
	
	if (Input::GetGamepad()->IsHeld(L_STICK_UP))
		NLE_LOG_TRACE("Stick is UP!!");
	if (Input::GetGamepad()->IsReleased(L_STICK_UP))
		NLE_LOG_TRACE("Stick is Released!!");
	if (Input::GetGamepad()->IsHeld(L_STICK_DOWN))
		NLE_LOG_TRACE("Stick is DOWN!!");
	if (Input::GetGamepad()->IsReleased(L_STICK_DOWN))
		NLE_LOG_TRACE("Stick is Released!!");
	
	if (Input::GetGamepad()->IsHeld(L_STICK_LEFT))
		NLE_LOG_TRACE("Stick is LEFT!!");
	if (Input::GetGamepad()->IsReleased(L_STICK_LEFT))
		NLE_LOG_TRACE("Stick is Released!!");
	if (Input::GetGamepad()->IsHeld(L_STICK_RIGHT))
		NLE_LOG_TRACE("Stick is RIGHT!!");
	if (Input::GetGamepad()->IsReleased(L_STICK_RIGHT))
		NLE_LOG_TRACE("Stick is Released!!");

	//if (Input::GetGamepad()->IsHeld(L_STICK_UP))
	//	NLE_LOG_TRACE("Stick is UP!!");
	//if (Input::GetGamepad()->IsReleased(L_STICK_UP))
	//	NLE_LOG_TRACE("Stick is Released!!");
	//if (Input::GetGamepad()->IsHeld(L_STICK_DOWN))
	//	NLE_LOG_TRACE("Stick is DOWN!!");
	//if (Input::GetGamepad()->IsReleased(L_STICK_DOWN))
	//	NLE_LOG_TRACE("Stick is Released!!");
	
	//if (Input::GetGamepad(1)->IsHeld(L_STICK_LEFT))
	//	NLE_LOG_TRACE("Controller two Stick is LEFT!!");
	//if (Input::GetGamepad(1)->IsReleased(L_STICK_LEFT))
	//	NLE_LOG_TRACE("Controller two Stick is Released!!");
	//if (Input::GetGamepad(1)->IsHeld(L_STICK_RIGHT))
	//	NLE_LOG_TRACE("Controller two Stick is RIGHT!!");
	//if (Input::GetGamepad(1)->IsReleased(L_STICK_RIGHT))
	//	NLE_LOG_TRACE("Controller two Stick is Released!!");
}

void MainLayer::OnImGuiRender()
{
}

void MainLayer::OnEvent(nle::Event& event)
{
}
