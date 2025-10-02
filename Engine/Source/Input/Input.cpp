#include "nle_pch.hpp"
#include "Input.hpp"

namespace nle
{
	Ref<Keyboard> Input::keyboard;
	Ref<Mouse> Input::mouse;

	void Input::Initialize()
	{
		keyboard = CreateRef<Keyboard>(256);
		mouse = CreateRef<Mouse>(8);

		Keyboard::SetCodes();
		Mouse::SetCodes();
	}

	void Input::Scan()
	{
		keyboard->Scan();
		mouse->Scan();
	}

	Ref<Keyboard> Input::GetKeyboard()
	{
		return keyboard;
	}

	Ref<Mouse> Input::GetMouse()
	{
		return mouse;
	}

	void Input::Reset()
	{
		mouse->Reset();
	}

	void Input::Close()
	{
	}
}
