#include "nle_pch.hpp"
#include "Gamepad.hpp"

#include "Input.hpp"

namespace nle
{
	Gamepad::Gamepad() : InputDevice()
	{
		mScanStates.resize(29);
		mDeadZone = 0.3f;

		mLeftTrigger  = 0.0f;
		mRightTrigger = 0.0f;

		mLeftThumbStick = {0.0f, 0.0f};
		mRightThumbStick = {0.0f, 0.0f};
	}

	Gamepad::Gamepad(SDL_Gamepad* handle, SDL_JoystickID id) : InputDevice()
	{
		mHandle = handle;
		mName = std::string(SDL_GetGamepadName(mHandle));

		mScanStates.resize(29);
		mDeadZone = 0.3f;

		mLeftTrigger = 0.0f;
		mRightTrigger = 0.0f;

		mLeftThumbStick = { 0.0f, 0.0f };
		mRightThumbStick = { 0.0f, 0.0f };
	}

	Gamepad::~Gamepad()
	{
	}

	void Gamepad::Close()
	{
		SDL_CloseGamepad(mHandle);
		mHandle = nullptr;
	}

	void Gamepad::SetDeadZone(float deadZone)
	{
		if (deadZone > 0.0f && deadZone < 1.0f)
			mDeadZone = deadZone;
		else if (deadZone < 0.0f)
			mDeadZone = 0.0f;
		else
			mDeadZone = 1.0f;
	}
}


