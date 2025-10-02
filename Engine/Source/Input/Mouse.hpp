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
	public:
		static std::unordered_map<size_t, int8_t> MapButtons;
	public:
		Mouse();
		Mouse(int32_t numOfStates);

		inline void SetPosition(const Vector2& pos) { mPosition = pos; }
		inline Vector2& GetPosition() { return mPosition; }

		bool IsPressed(uint16_t code) override;
		bool IsHeld(uint16_t code) override;
		bool IsReleased(uint16_t code) override;

		static void SetCodes();
	};
}
