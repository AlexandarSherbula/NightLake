#include "nle_pch.hpp"
#include "InputDevices.hpp"


namespace nle
{
	InputDevice::InputDevice()
	{

	}

	InputDevice::InputDevice(int32_t numOfStates)
	{
		mScanStates.resize(numOfStates);
	}

	void InputDevice::Scan()
	{
		for (ScanState& scanState : mScanStates)
			scanState.Update();
	}

	void InputDevice::SetNewState(int32_t code, bool state)
	{
		mScanStates[code].isNew = state;
	}

	InputDevice::ScanState::ScanState()
	{
		inputState = { false };
		isNew = false;
		isOld = false;
	}

	void InputDevice::ScanState::Update()
	{
		inputState.pressed = false;
		inputState.released = false;

		if (isNew != isOld)
		{
			if (isNew)
			{
				inputState.pressed = !inputState.held;
				inputState.held = true;
			}
			else
			{
				inputState.released = true;
				inputState.held = false;
			}
		}

		isOld = isNew;
	}
}
