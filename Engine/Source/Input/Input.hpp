#pragma once

#include "InputDevices.hpp"
#include "Keyboard.hpp"
#include "Mouse.hpp"
#include "Gamepad.hpp"

namespace nle
{
	class Input
	{
	private:
		static Ref<Keyboard> keyboard;
		static Ref<Mouse> mouse;
		static std::vector<std::unique_ptr<Gamepad>> gamepads;
		static inline Gamepad dummy;
	public:
		static void Initialize();
		static void Scan();
		static void Reset();
		static void Close();

		static Ref<Keyboard> GetKeyboard();
		static Ref<Mouse> GetMouse();
		static Gamepad* GetGamepad(int32_t index = 0);
		static bool IsGamePadConnected(int32_t index = 0);

		static void AddGamepad(SDL_JoystickID id);
		static void RemoveGamepad(SDL_JoystickID id);

		static void ProcessGamePadEvents(SDL_Event& event);
	};
}
