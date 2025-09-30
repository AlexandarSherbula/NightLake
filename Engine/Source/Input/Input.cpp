#include "nle_pch.hpp"
#include "Input.hpp"

namespace nle
{
	std::array<bool, 256> Input::oldKeyState = { false };
	std::array<bool, 256> Input::newKeyState = { false };
	std::array<Input::States, 256> Input::keyStates = { false };

	std::array<bool, 8> Input::oldMouseButtonState = { false };
	std::array<bool, 8> Input::newMouseButtonState = { false };
	std::array<Input::States, 8> Input::mouseButtonStates = { false };

	std::unordered_map<size_t, int8_t> Input::mapKeys;

	void Input::Scan()
	{
		auto scan = [](Input::States& state, bool& oldState, bool& newState)
			{
				state.pressed = false;
				state.released = false;

				if (newState != oldState)
				{
					if (newState)
					{
						state.pressed = !state.held;
						state.held = true;
					}
					else
					{
						state.released = true;
						state.held = false;
					}
				}

				oldState = newState;
			};

		for (int i = 0; i < keyStates.size(); i++)
			scan(keyStates[i], oldKeyState[i], newKeyState[i]);

		for (int i = 0; i < mouseButtonStates.size(); i++)
			scan(mouseButtonStates[i], oldMouseButtonState[i], newMouseButtonState[i]);
	}

	void Input::UpdateKeyState(int32_t keycode, bool state)
	{
		newKeyState[keycode] = state;
	}

	void Input::UpdateMouseState(int32_t mousebutton, bool state)
	{
		newMouseButtonState[mousebutton] = state;
	}

	Vector2 Input::GetMousePosition()
	{
		//return Engine::Get()->GetWindow()->GetMousePositionFromWindowAPI();
		return Vector2();
	}

	void Input::SetCodes()
	{
#if defined(NLE_API_OPENGL) && defined(NLE_API_DX11)
		SetSDL_InputCodes(mapKeys);
		SetWin32KeyCodes(mapKeys);
#elif defined(NLE_API_OPENGL)
		SetSDL_InputCodes(mapKeys);
#elif defined(NLE_API_DX11)
		SetWin32KeyCodes(mapKeys);
#endif
	}
}