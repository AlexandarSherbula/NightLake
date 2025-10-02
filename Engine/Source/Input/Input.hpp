#pragma once

#include "InputDevices.hpp"
#include "Keyboard.hpp"
#include "Mouse.hpp"

namespace nle
{
	class Input
	{
	private:
		static Ref<Keyboard> keyboard;
		static Ref<Mouse> mouse;
	public:
		static void Initialize();
		static void Close();
		static void Scan();

		static Ref<Keyboard> GetKeyboard();
		static Ref<Mouse> GetMouse();
	};
}
