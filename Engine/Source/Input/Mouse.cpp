#include "nle_pch.hpp"
#include "Mouse.hpp"

namespace nle
{
	std::unordered_map<size_t, int8_t> Mouse::MapButtons;

	Mouse::Mouse()
	{
	}

	Mouse::Mouse(int32_t numOfStates) : InputDevice(numOfStates)
	{
	}

	bool Mouse::IsPressed(uint16_t code)
	{
		if (code > 4)
		{
			NLE_LOG_ERROR("SDL doesn't support more than two inputs");
			return false;
		}
		return mScanStates[code].inputState.pressed;
	}

	bool Mouse::IsHeld(uint16_t code)
	{
		if (code > 4)
		{
			NLE_LOG_ERROR("SDL doesn't support more than two inputs");
			return false;
		}
		return mScanStates[code].inputState.held;
	}

	bool Mouse::IsReleased(uint16_t code)
	{
		if (code > 4)
		{
			NLE_LOG_ERROR("SDL doesn't support more than two inputs");
			return false;
		}
		return mScanStates[code].inputState.released;
	}

	void Mouse::SetCodes()
	{
		MapButtons[SDL_BUTTON_LEFT]   = L_BUTTON;
		MapButtons[SDL_BUTTON_RIGHT]  = R_BUTTON;
		MapButtons[SDL_BUTTON_MIDDLE] = M_BUTTON;
		MapButtons[SDL_BUTTON_X1]     = X_BUTTON1;
		MapButtons[SDL_BUTTON_X2]     = X_BUTTON2;
	}


}


