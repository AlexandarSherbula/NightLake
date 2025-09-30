#pragma once

#include "Math/Math.hpp"
#include "InputCodes.hpp"

#include <unordered_map>
#include <array>

namespace nle
{
	class Input
	{
	public:
		struct States
		{
			bool pressed = false;
			bool held = false;
			bool released = false;
		};
	private:
		static std::array<States, 256> keyStates;
		static std::array<bool, 256> newKeyState;
		static std::array<bool, 256> oldKeyState;

		static std::array<States, 8> mouseButtonStates;
		static std::array<bool, 8> newMouseButtonState;
		static std::array<bool, 8> oldMouseButtonState;

		static std::unordered_map<size_t, int8_t> mapKeys;
	public:
		static void SetCodes();
		static void Scan();
		static void UpdateKeyState(int32_t keycode, bool state);
		static void UpdateMouseState(int32_t mousebutton, bool state);

		inline static int8_t GetMapKey(int32_t keycode) { return mapKeys[keycode]; }

		inline static States GetKeyState(int keycode) { return keyStates[keycode]; }

		static bool KeyPressed(int32_t keycode) { return keyStates[keycode].pressed; }
		static bool KeyHeld(int32_t keycode) { return keyStates[keycode].held; }
		static bool KeyReleased(int32_t keycode) { return keyStates[keycode].released; }

		inline static bool MouseButtonPressed(int32_t mb) { return mouseButtonStates[mb].pressed; }
		inline static bool MouseButtonHeld(int32_t mb) { return mouseButtonStates[mb].held; }
		inline static bool MouseButtonReleased(int32_t mb) { return mouseButtonStates[mb].released; }
		static Vector2 GetMousePosition();
	};
}