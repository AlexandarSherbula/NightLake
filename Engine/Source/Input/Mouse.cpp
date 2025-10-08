#include "aio_pch.hpp"
#include "Mouse.hpp"

namespace aio
{
	std::unordered_map<size_t, int8_t> Mouse::MapButtons;

	Mouse::Mouse()
	{
		mScanStates.resize(8);
		mMouseWheel = { 0, 0 };
	}

	Mouse::~Mouse()
	{
	}

	bool Mouse::IsPressed(uint16_t code)
	{
		AIO_ASSERT(code < 5, "SDL doesn't support more than two extra  buttons");
		return mScanStates[code].inputState.pressed;
	}

	bool Mouse::IsHeld(uint16_t code)
	{
		AIO_ASSERT(code < 5, "SDL doesn't support more than two extra buttons");
		return mScanStates[code].inputState.held;
	}

	bool Mouse::IsReleased(uint16_t code)
	{
		AIO_ASSERT(code < 5, "SDL doesn't support more than two extra  buttons");
		return mScanStates[code].inputState.released;
	}

	void Mouse::NewMouseWheelState(const Vector2& mouseWheel)
	{
		mMouseWheel = mouseWheel;
	}

	void Mouse::SetCodes()
	{
		MapButtons[SDL_BUTTON_LEFT]   = L_BUTTON;
		MapButtons[SDL_BUTTON_RIGHT]  = R_BUTTON;
		MapButtons[SDL_BUTTON_MIDDLE] = M_BUTTON;
		MapButtons[SDL_BUTTON_X1]     = X_BUTTON1;
		MapButtons[SDL_BUTTON_X2]     = X_BUTTON2;
	}

	void Mouse::Reset()
	{
		mMouseWheel = { 0, 0 };
	}


}


