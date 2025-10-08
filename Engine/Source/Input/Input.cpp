#include "aio_pch.hpp"
#include "Input.hpp"

namespace aio
{
	Ref<Keyboard> Input::keyboard;
	Ref<Mouse> Input::mouse;
	std::vector<Scope<Gamepad>> Input::gamepads;

	void Input::Init()
	{
		keyboard = CreateRef<Keyboard>();
		mouse = CreateRef<Mouse>();

		gamepads.reserve(4);

		Keyboard::SetCodes();
		Mouse::SetCodes();

		AIO_ASSERT(SDL_Init(SDL_INIT_GAMEPAD | SDL_INIT_HAPTIC), "Failed to initalize SDL");
	}

	void Input::Scan()
	{
		keyboard->Scan();
		mouse->Scan();

		if (gamepads.size() != 0)
			for (auto& gp : gamepads)
				gp->Scan();
	}

	Ref<Keyboard> Input::GetKeyboard()
	{
		return keyboard;
	}

	Ref<Mouse> Input::GetMouse()
	{
		return mouse;
	}

	Gamepad* Input::GetGamepad(int32_t index)
	{
		if (IsGamePadConnected(index))
			return gamepads[index].get();

		AIO_LOG_WARN("There is no controller at index {0} connected", index);
		return &dummy;
	}

	bool Input::IsGamePadConnected(int32_t index)
	{
		for (int32_t i = 0; i < gamepads.size(); i++)
		{
			if (i == index)
				return true;
		}
		return false;
	}

	void Input::AddGamepad(SDL_JoystickID id)
	{
		SDL_Gamepad* handle = SDL_OpenGamepad(id);
		if (handle)
		{
			gamepads.emplace_back(CreateScope<Gamepad>(handle, id));
			AIO_LOG_INFO("Gamepad connected: " + std::string(SDL_GetGamepadName(handle)));
		}
		else
		{
			AIO_LOG_ERROR("Failed to open gamepad: " + std::string(SDL_GetError()));
		}
	}

	void Input::RemoveGamepad(SDL_JoystickID id)
	{
		gamepads.erase
		(
			std::remove_if(gamepads.begin(), gamepads.end(),
				[id](const Scope<Gamepad>& g)
				{
					if (SDL_GetGamepadID(g->mHandle) == id) 
					{
						AIO_LOG_WARN("Gamepad removed: " + std::string(SDL_GetGamepadName(g->GetHandle())));
						return true;
					}
					return false;
				}),
		
			gamepads.end()
		);
	}

	void Input::ProcessGamePadEvents(SDL_Event& sdl_event)
	{
		switch (sdl_event.type)
		{
			case SDL_EVENT_GAMEPAD_ADDED: {
				SDL_JoystickID id = sdl_event.gdevice.which;
				AddGamepad(id);
				break;
			}
			case SDL_EVENT_GAMEPAD_REMOVED: 
			{
				SDL_JoystickID id = sdl_event.gdevice.which;
				RemoveGamepad(id);
				break;
			}
			case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
			{
				for (auto& gp : gamepads)
				{
					if (sdl_event.gbutton.which == SDL_GetGamepadID(gp->mHandle))
					{
						gp->SetNewState(sdl_event.gbutton.button, true);
					}
				}
				break;
			}
			case SDL_EVENT_GAMEPAD_BUTTON_UP:
			{
				for (auto& gp : gamepads)
				{
					if (sdl_event.gbutton.which == SDL_GetGamepadID(gp->mHandle))
						gp->SetNewState(sdl_event.gbutton.button, false);
				}
				break;
			}
			case SDL_EVENT_GAMEPAD_AXIS_MOTION:
			{
				float normalizedValue = 0.0f;

				auto Normalize = [&](float axisValue)
				{
					normalizedValue = axisValue / 32767.0f; // float division
					// optional: clamp to [-1,1] to be safe
					if (normalizedValue > 1.0f) normalizedValue = 1.0f;
					if (normalizedValue < -1.0f) normalizedValue = -1.0f;

					return normalizedValue;
				};

				switch (sdl_event.gaxis.axis)
				{					
					case SDL_GAMEPAD_AXIS_LEFTX:
					{
						for (auto& gp : gamepads)
						{
							if (sdl_event.gbutton.which == SDL_GetGamepadID(gp->mHandle))
							{
								gp->mLeftThumbStick.x = Normalize(sdl_event.gaxis.value);

								if (gp->mLeftThumbStick.x < -gp->mDeadZone)
									gp->SetNewState(L_STICK_LEFT, true);
								else if (gp->mLeftThumbStick.x >= -gp->mDeadZone && gp->mLeftThumbStick.x <= 0.0f && gp->mScanStates[L_STICK_LEFT].isOld)
									gp->SetNewState(L_STICK_LEFT, false);

								if (gp->mLeftThumbStick.x > gp->mDeadZone)
									gp->SetNewState(L_STICK_RIGHT, true);
								else if (gp->mLeftThumbStick.x >= 0.0f && gp->mLeftThumbStick.x <= gp->mDeadZone && gp->mScanStates[L_STICK_RIGHT].isOld)
									gp->SetNewState(L_STICK_RIGHT, false);
							}
						}
						break;
					}
					case SDL_GAMEPAD_AXIS_LEFTY:
					{
						for (auto& gp : gamepads)
						{
							if (sdl_event.gbutton.which == SDL_GetGamepadID(gp->mHandle))
							{
								gp->mLeftThumbStick.y = Normalize(sdl_event.gaxis.value);
								
								if (gp->mLeftThumbStick.y < -gp->mDeadZone)
									gp->SetNewState(L_STICK_UP, true);
								else if (gp->mLeftThumbStick.y >= -gp->mDeadZone && gp->mLeftThumbStick.y <= 0.0f && gp->mScanStates[L_STICK_UP].isOld)
									gp->SetNewState(L_STICK_UP, false);
								
								if (gp->mLeftThumbStick.y > gp->mDeadZone)
									gp->SetNewState(L_STICK_DOWN, true);
								else if (gp->mLeftThumbStick.y >= 0.0f && gp->mLeftThumbStick.y <= gp->mDeadZone && gp->mScanStates[L_STICK_DOWN].isOld)
									gp->SetNewState(L_STICK_DOWN, false);
							}
						}
						break;
					}
					case SDL_GAMEPAD_AXIS_RIGHTX:
					{
						for (auto& gp : gamepads)
						{
							if (sdl_event.gbutton.which == SDL_GetGamepadID(gp->mHandle))
							{
								gp->mRightThumbStick.x = Normalize(sdl_event.gaxis.value);

								if (gp->mRightThumbStick.x < -gp->mDeadZone)
									gp->SetNewState(R_STICK_LEFT, true);
								else if (gp->mRightThumbStick.x >= -gp->mDeadZone && gp->mRightThumbStick.x <= 0.0f && gp->mScanStates[R_STICK_LEFT].isOld)
									gp->SetNewState(R_STICK_LEFT, false);

								if (gp->mRightThumbStick.x > gp->mDeadZone)
									gp->SetNewState(R_STICK_RIGHT, true);
								else if (gp->mRightThumbStick.x >= 0.0f && gp->mRightThumbStick.x <= gp->mDeadZone && gp->mScanStates[R_STICK_RIGHT].isOld)
									gp->SetNewState(R_STICK_RIGHT, false);
							}
						}
						break;
					}
					case SDL_GAMEPAD_AXIS_RIGHTY:
					{
						for (auto& gp : gamepads)
						{
							if (sdl_event.gbutton.which == SDL_GetGamepadID(gp->mHandle))
							{
								gp->mRightThumbStick.y = Normalize(sdl_event.gaxis.value);
								
								if (gp->mRightThumbStick.y < -gp->mDeadZone)
									gp->SetNewState(R_STICK_UP, true);
								else if (gp->mRightThumbStick.y >= -gp->mDeadZone && gp->mRightThumbStick.y <= 0.0f && gp->mScanStates[R_STICK_UP].isOld)
									gp->SetNewState(R_STICK_UP, false);
								
								if (gp->mRightThumbStick.y > gp->mDeadZone)
									gp->SetNewState(R_STICK_DOWN, true);
								else if (gp->mRightThumbStick.y >= 0.0f && gp->mRightThumbStick.y <= gp->mDeadZone && gp->mScanStates[R_STICK_DOWN].isOld)
									gp->SetNewState(R_STICK_DOWN, false);
							}
						}
						break;
					}
					case SDL_GAMEPAD_AXIS_LEFT_TRIGGER:
					{
						for (auto& gp : gamepads)
						{
							if (sdl_event.gbutton.which == SDL_GetGamepadID(gp->mHandle))
							{
								gp->mLeftTrigger = Normalize(sdl_event.gaxis.value);
							}
						}
						break;
					}
					case SDL_GAMEPAD_AXIS_RIGHT_TRIGGER:
					{
						for (auto& gp : gamepads)
						{
							if (sdl_event.gbutton.which == SDL_GetGamepadID(gp->mHandle))
							{
								gp->mRightTrigger = Normalize(sdl_event.gaxis.value);
							}
						}
						break;
					}
				}
				break;
			}
		}
	}

	void Input::Reset()
	{
		mouse->Reset();
	}

	void Input::Close()
	{
		gamepads.clear();
		SDL_QuitSubSystem(SDL_INIT_GAMEPAD);
	}
}
