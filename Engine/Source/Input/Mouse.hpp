#pragma once


#include "InputDevices.hpp"

#include "Math/Math.hpp"

namespace nle
{
	enum MouseButton
	{
		L_BUTTON,
		R_BUTTON,
		M_BUTTON,
		X_BUTTON1,
		X_BUTTON2,
		X_BUTTON3,
		X_BUTTON4,
		X_BUTTON5,
	};

	class Mouse : public InputDevice
	{
	private:
		Vector2 mPosition;
		Vector2 mMouseWheel;
	public:
		static std::unordered_map<size_t, int8_t> MapButtons;
	public:
		Mouse();
		~Mouse();

		inline void SetPosition(const Vector2& pos) { mPosition = pos; }

		inline Vector2 GetPosition() { return mPosition; }
		inline float X() const { return mPosition.x; }
		inline float Y() const { return mPosition.y; }

		bool IsPressed(uint16_t code) override;
		bool IsHeld(uint16_t code) override;
		bool IsReleased(uint16_t code) override;

		void NewMouseWheelState(const Vector2& mouseWheel);
		Vector2 Wheel() { return mMouseWheel; }

		static void SetCodes();

		void Reset() override;
	};
}
