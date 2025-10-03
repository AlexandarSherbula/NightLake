#pragma once

#include "InputDevices.hpp"
#include "Math/Math.hpp"

#include "SDL3/SDL.h"

#include <string>

enum GamepadButtonCode
{
	FACE_DOWN,
	FACE_RIGHT,
	FACE_LEFT,
	FACE_UP,
	SELECT,
	SHARE = 4,
	POWER,
	START,
	OPTIONS = 6,
	L_STICK_PUSH,
	R_STICK_PUSH,
	LEFT_SHOULDER,
	RIGHT_SHOULDER,
	D_PAD_UP,
	D_PAD_DOWN,
	D_PAD_LEFT,
	D_PAD_RIGHT,
	BUTTON_MISC1,	           //Misc 1 (touchpad button, etc.)
	BUTTON_PADDLE1,	           //Paddle buttons(if present)
	BUTTON_PADDLE2,	           //Paddle 2
	BUTTON_PADDLE3,	           //Paddle 3
	BUTTON_PADDLE4,	           //Paddle 4
	BUTTON_TOUCHPAD,	       //Touchpad pressed(DualShock / DualSense)
	L_STICK_UP,
	L_STICK_DOWN,
	L_STICK_LEFT,
	L_STICK_RIGHT,
	R_STICK_UP,
	R_STICK_DOWN,
	R_STICK_LEFT,
	R_STICK_RIGHT,
};

namespace nle
{
	class Gamepad : public InputDevice
	{
	private:
		SDL_Gamepad* mHandle;
		std::string mName;

		Vector2 mLeftThumbStick;
		Vector2 mRightThumbStick;

		float mLeftTrigger;
		float mRightTrigger;

		float mDeadZone;
	public:
		Gamepad();
		Gamepad(SDL_Gamepad* handle, SDL_JoystickID id);

		~Gamepad();
		void Close();

		inline SDL_Gamepad* GetHandle() { return mHandle; }
		inline SDL_JoystickID ID() { return SDL_GetGamepadID(mHandle); }

		inline float DeadZone() { return (mHandle == nullptr) ?  0.0f : mDeadZone; }
		void SetDeadZone(float deadZone);

		inline Vector2 LeftThumbStick() { return (mHandle == nullptr) ? Vector2(0.0f, 0.0f) : mLeftThumbStick; }
		inline Vector2 RightThumbStick() { return (mHandle == nullptr) ? Vector2(0.0f, 0.0f) : mRightThumbStick; }

		inline float LeftTrigger() { return (mHandle == nullptr) ? 0.0f : mLeftTrigger; }
		inline float RightTrigger() { return (mHandle == nullptr) ? 0.0f : mRightTrigger; }

		bool IsPressed(uint16_t code)  override { return (mHandle == nullptr) ? false : mScanStates[code].inputState.pressed; }
		bool IsHeld(uint16_t code)     override { return (mHandle == nullptr) ? false : mScanStates[code].inputState.held; }
		bool IsReleased(uint16_t code) override { return (mHandle == nullptr) ? false : mScanStates[code].inputState.released; }		

		friend class Input;
	};
}