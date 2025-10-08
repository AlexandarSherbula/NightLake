#pragma once

#include <vector>

namespace aio
{
	class InputDevice
	{
	protected:
		struct InputState
		{
			bool pressed;
			bool held;
			bool released;
		};

		struct ScanState
		{
		public:
			InputState inputState = { false };
			bool isNew = false;
			bool isOld = false;
		public:
			ScanState();
			void Update();
		};

		std::vector<ScanState> mScanStates;
	public:
		InputDevice();
	public:
		void SetNewState(int32_t code, bool state);
		void Scan();
		virtual void Reset() {}

		inline std::vector<ScanState>& GetScanStates() { return mScanStates; }
		virtual bool IsPressed(uint16_t code) { return mScanStates[code].inputState.pressed; }
		virtual bool IsHeld(uint16_t code) { return mScanStates[code].inputState.held; }
		virtual bool IsReleased(uint16_t code) { return mScanStates[code].inputState.released; }
	};
}

