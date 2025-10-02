#include "nle_pch.hpp"
#include "Input.hpp"

namespace nle
{
	Ref<Keyboard> Input::keyboard;
	Ref<Mouse> Input::mouse;
	std::vector<Gamepad> Input::gamepads;

	void Input::Initialize()
	{
		keyboard = CreateRef<Keyboard>();
		mouse = CreateRef<Mouse>();

		Keyboard::SetCodes();
		Mouse::SetCodes();

		NLE_ASSERT(SDL_Init(SDL_INIT_GAMEPAD | SDL_INIT_HAPTIC), "Failed to initalize SDL");
	}

	void Input::Scan()
	{
		keyboard->Scan();
		mouse->Scan();

		if (gamepads.size() != 0)
			for (auto& gp : gamepads)
				gp.Scan();
	}

	Ref<Keyboard> Input::GetKeyboard()
	{
		return keyboard;
	}

	Ref<Mouse> Input::GetMouse()
	{
		return mouse;
	}

	Gamepad& Input::GetGamepad(int32_t index)
	{
		if (gamepads.size() != 0)
		{
			NLE_ASSERT(index < gamepads.size(), "Accessing index that has not been addded!");
			return gamepads[index];
		}
		else
		{
			NLE_LOG_WARN("There are no controllers plugged in");
			Gamepad dud;
			return dud;
		}
	}

	void Input::AddGamepad(SDL_JoystickID id)
	{
		SDL_Gamepad* handle = SDL_OpenGamepad(id);
		if (handle)
		{
			gamepads.push_back({ handle, id });
			NLE_LOG_INFO("Gamepad connected: " + std::string(SDL_GetGamepadName(handle)));
		}
		else
		{
			NLE_LOG_ERROR("Failed to open gamepad: " + std::string(SDL_GetError()));
		}
	}

	void Input::RemoveGamepad(SDL_JoystickID id)
	{
		gamepads.erase
		(
			std::remove_if(gamepads.begin(), gamepads.end(),
				[id](Gamepad& g) {
					if (SDL_GetGamepadID(g.GetHandle()) == id) {
						NLE_LOG_WARN("Gamepad removed: " + std::string(SDL_GetGamepadName(g.GetHandle())));
						g.Close();
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
					if (sdl_event.gbutton.which == gp.ID())
					{
						gp.SetNewState(sdl_event.gbutton.button, true);
					}
				}
				break;
			}
			case SDL_EVENT_GAMEPAD_BUTTON_UP:
			{
				for (auto& gp : gamepads)
				{
					if (sdl_event.gbutton.which == gp.ID())
						gp.SetNewState(sdl_event.gbutton.button, false);
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
							if (sdl_event.gbutton.which == gp.ID())
							{
								gp.LeftThumbStick().x = Normalize(sdl_event.gaxis.value);

								if (gp.LeftThumbStick().x < -gp.DeadZone())
									gp.SetNewState(L_STICK_LEFT, true);
								else if (gp.LeftThumbStick().x >= -gp.DeadZone() && gp.LeftThumbStick().x <= 0.0f && gp.GetScanStates()[L_STICK_LEFT].isOld)
									gp.SetNewState(L_STICK_LEFT, false);

								if (gp.LeftThumbStick().x > gp.DeadZone())
									gp.SetNewState(L_STICK_RIGHT, true);
								else if (gp.LeftThumbStick().x >= 0.0f && gp.LeftThumbStick().x <= gp.DeadZone() && gp.GetScanStates()[L_STICK_RIGHT].isOld)
									gp.SetNewState(L_STICK_RIGHT, false);
							}
						}
						break;
					}
					case SDL_GAMEPAD_AXIS_LEFTY:
					{
						for (auto& gp : gamepads)
						{
							if (sdl_event.gbutton.which == gp.ID())
							{
								gp.LeftThumbStick().y = Normalize(sdl_event.gaxis.value);
								
								if (gp.LeftThumbStick().y < -gp.DeadZone())
									gp.SetNewState(L_STICK_UP, true);
								else if (gp.LeftThumbStick().y >= -gp.DeadZone() && gp.LeftThumbStick().y <= 0.0f && gp.GetScanStates()[L_STICK_UP].isOld)
									gp.SetNewState(L_STICK_UP, false);
								
								if (gp.LeftThumbStick().y > gp.DeadZone())
									gp.SetNewState(L_STICK_DOWN, true);
								else if (gp.LeftThumbStick().y >= 0.0f && gp.LeftThumbStick().y <= gp.DeadZone() && gp.GetScanStates()[L_STICK_DOWN].isOld)
									gp.SetNewState(L_STICK_DOWN, false);
							}
						}
						break;
					}
					case SDL_GAMEPAD_AXIS_RIGHTX:
					{
						for (auto& gp : gamepads)
						{
							if (sdl_event.gbutton.which == gp.ID())
							{
								gp.RightThumbStick().x = Normalize(sdl_event.gaxis.value);

								if (gp.RightThumbStick().x < -gp.DeadZone())
									gp.SetNewState(R_STICK_LEFT, true);
								else if (gp.RightThumbStick().x >= -gp.DeadZone() && gp.RightThumbStick().x <= 0.0f && gp.GetScanStates()[R_STICK_LEFT].isOld)
									gp.SetNewState(R_STICK_LEFT, false);

								if (gp.RightThumbStick().x > gp.DeadZone())
									gp.SetNewState(R_STICK_RIGHT, true);
								else if (gp.RightThumbStick().x >= 0.0f && gp.RightThumbStick().x <= gp.DeadZone() && gp.GetScanStates()[R_STICK_RIGHT].isOld)
									gp.SetNewState(R_STICK_RIGHT, false);
							}
						}
						break;
					}
					case SDL_GAMEPAD_AXIS_RIGHTY:
					{
						for (auto& gp : gamepads)
						{
							if (sdl_event.gbutton.which == gp.ID())
							{
								gp.RightThumbStick().y = Normalize(sdl_event.gaxis.value);
								
								if (gp.RightThumbStick().y < -gp.DeadZone())
									gp.SetNewState(R_STICK_UP, true);
								else if (gp.RightThumbStick().y >= -gp.DeadZone() && gp.RightThumbStick().y <= 0.0f && gp.GetScanStates()[R_STICK_UP].isOld)
									gp.SetNewState(R_STICK_UP, false);
								
								if (gp.RightThumbStick().y > gp.DeadZone())
									gp.SetNewState(R_STICK_DOWN, true);
								else if (gp.RightThumbStick().y >= 0.0f && gp.RightThumbStick().y <= gp.DeadZone() && gp.GetScanStates()[R_STICK_DOWN].isOld)
									gp.SetNewState(R_STICK_DOWN, false);
							}
						}
						break;
					}
					case SDL_GAMEPAD_AXIS_LEFT_TRIGGER:
					{
						for (auto& gp : gamepads)
						{
							if (sdl_event.gbutton.which == gp.ID())
							{
								gp.LeftTrigger() = Normalize(sdl_event.gaxis.value);
							}
						}
						break;
					}
					case SDL_GAMEPAD_AXIS_RIGHT_TRIGGER:
					{
						for (auto& gp : gamepads)
						{
							if (sdl_event.gbutton.which == gp.ID())
							{
								gp.RightTrigger() = Normalize(sdl_event.gaxis.value);
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
		for (auto& gp : gamepads) 
		{
			gp.Close();
		}
		gamepads.clear();
		SDL_QuitSubSystem(SDL_INIT_GAMEPAD);
	}
}
