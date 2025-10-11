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
	
	if (Input::GetMouse()->IsHeld(L_BUTTON))
		AIO_LOG_TRACE("Left click was pressed: x: {0}, y: {1}", Input::GetMouse()->X(), Input::GetMouse()->Y());
	
	if (Input::GetMouse()->IsReleased(L_BUTTON))
		AIO_LOG_TRACE("Left click was released.");

	if (Input::GetMouse()->WheelY() != 0.0f)
		AIO_LOG_TRACE("Wheel: {0}", Input::GetMouse()->WheelY());
	
	//AIO_LOG_TRACE("LeftStick x: {0}, y: {1}", Input::GetGamepad()->LeftThumbStick().x, Input::GetGamepad()->LeftThumbStick().y);
	//AIO_LOG_TRACE("LeftTrigger: {0}, RightTrigger: {1}", Input::GetGamepad()->LeftTrigger(), Input::GetGamepad()->RightTrigger());
	
	//if (Input::GetGamepad()->IsHeld(L_STICK_UP))
	//	AIO_LOG_TRACE("Stick is UP!!");
	//if (Input::GetGamepad()->IsReleased(L_STICK_UP))
	//	AIO_LOG_TRACE("Stick is Released!!");
	//if (Input::GetGamepad()->IsHeld(L_STICK_DOWN))
	//	AIO_LOG_TRACE("Stick is DOWN!!");
	//if (Input::GetGamepad()->IsReleased(L_STICK_DOWN))
	//	AIO_LOG_TRACE("Stick is Released!!");

	//if (Input::GetGamepad()->IsHeld(L_STICK_LEFT))
	//	AIO_LOG_TRACE("Stick is LEFT!!");
	//if (Input::GetGamepad()->IsReleased(L_STICK_LEFT))
	//	AIO_LOG_TRACE("Stick is Released!!");
	//if (Input::GetGamepad()->IsHeld(L_STICK_RIGHT))
	//	AIO_LOG_TRACE("Stick is RIGHT!!");
	//if (Input::GetGamepad()->IsReleased(L_STICK_RIGHT))
	//	AIO_LOG_TRACE("Stick is Released!!");

	//if (Input::GetGamepad()->IsHeld(L_STICK_UP))
	//	AIO_LOG_TRACE("Stick is UP!!");
	//if (Input::GetGamepad()->IsReleased(L_STICK_UP))
	//	AIO_LOG_TRACE("Stick is Released!!");
	//if (Input::GetGamepad()->IsHeld(L_STICK_DOWN))
	//	AIO_LOG_TRACE("Stick is DOWN!!");
	//if (Input::GetGamepad()->IsReleased(L_STICK_DOWN))
	//	AIO_LOG_TRACE("Stick is Released!!");
	
	//if (Input::GetGamepad(1)->IsHeld(L_STICK_LEFT))
	//	AIO_LOG_TRACE("Controller two Stick is LEFT!!");
	//if (Input::GetGamepad(1)->IsReleased(L_STICK_LEFT))
	//	AIO_LOG_TRACE("Controller two Stick is Released!!");
	//if (Input::GetGamepad(1)->IsHeld(L_STICK_RIGHT))
	//	AIO_LOG_TRACE("Controller two Stick is RIGHT!!");
	//if (Input::GetGamepad(1)->IsReleased(L_STICK_RIGHT))
	//	AIO_LOG_TRACE("Controller two Stick is Released!!");
}

void MainLayer::OnImGuiRender()
{
}

void MainLayer::OnEvent(aio::Event& event)
{
}
