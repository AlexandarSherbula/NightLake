#include "nle_pch.hpp"
#include "Keyboard.hpp"

namespace nle
{
	std::unordered_map<size_t, int8_t> Keyboard::MapKeys;

	Keyboard::Keyboard() : InputDevice()
	{
	}

	Keyboard::~Keyboard()
	{
		NLE_LOG_INFO("Destroyed");
	}

	Keyboard::Keyboard(int32_t numOfStates) : InputDevice(numOfStates)
	{
		NLE_LOG_INFO("Constructed");
	}

	void Keyboard::SetCodes()
	{
		MapKeys[0x00] = KeyCode::NONE;

		MapKeys[SDL_SCANCODE_A] = KeyCode::A; MapKeys[SDL_SCANCODE_B] = KeyCode::B; MapKeys[SDL_SCANCODE_C] = KeyCode::C; MapKeys[SDL_SCANCODE_D] = KeyCode::D; MapKeys[SDL_SCANCODE_E] = KeyCode::E;
		MapKeys[SDL_SCANCODE_F] = KeyCode::F; MapKeys[SDL_SCANCODE_G] = KeyCode::G; MapKeys[SDL_SCANCODE_H] = KeyCode::H; MapKeys[SDL_SCANCODE_I] = KeyCode::I; MapKeys[SDL_SCANCODE_J] = KeyCode::J;
		MapKeys[SDL_SCANCODE_K] = KeyCode::K; MapKeys[SDL_SCANCODE_L] = KeyCode::L; MapKeys[SDL_SCANCODE_M] = KeyCode::M; MapKeys[SDL_SCANCODE_N] = KeyCode::N; MapKeys[SDL_SCANCODE_O] = KeyCode::O;
		MapKeys[SDL_SCANCODE_P] = KeyCode::P; MapKeys[SDL_SCANCODE_Q] = KeyCode::Q; MapKeys[SDL_SCANCODE_R] = KeyCode::R; MapKeys[SDL_SCANCODE_S] = KeyCode::S; MapKeys[SDL_SCANCODE_T] = KeyCode::T;
		MapKeys[SDL_SCANCODE_U] = KeyCode::U; MapKeys[SDL_SCANCODE_V] = KeyCode::V; MapKeys[SDL_SCANCODE_W] = KeyCode::W; MapKeys[SDL_SCANCODE_X] = KeyCode::X; MapKeys[SDL_SCANCODE_E] = KeyCode::Y;
		MapKeys[SDL_SCANCODE_Z] = KeyCode::Z;

		MapKeys[SDL_SCANCODE_F1] = KeyCode::F1; MapKeys[SDL_SCANCODE_F2] = KeyCode::F2; MapKeys[SDL_SCANCODE_F3] = KeyCode::F3; MapKeys[SDL_SCANCODE_F4] = KeyCode::F4;
		MapKeys[SDL_SCANCODE_F5] = KeyCode::F5; MapKeys[SDL_SCANCODE_F6] = KeyCode::F6; MapKeys[SDL_SCANCODE_F7] = KeyCode::F7; MapKeys[SDL_SCANCODE_F8] = KeyCode::F8;
		MapKeys[SDL_SCANCODE_F9] = KeyCode::F9; MapKeys[SDL_SCANCODE_F10] = KeyCode::F10; MapKeys[SDL_SCANCODE_F11] = KeyCode::F11; MapKeys[SDL_SCANCODE_F12] = KeyCode::F12;

		MapKeys[SDL_SCANCODE_DOWN] = KeyCode::DOWN; MapKeys[SDL_SCANCODE_LEFT] = KeyCode::LEFT; MapKeys[SDL_SCANCODE_RIGHT] = KeyCode::RIGHT; MapKeys[SDL_SCANCODE_UP] = KeyCode::UP;

		MapKeys[SDL_SCANCODE_BACKSPACE] = KeyCode::BACK; MapKeys[SDL_SCANCODE_ESCAPE] = KeyCode::ESCAPE; MapKeys[SDL_SCANCODE_RETURN] = KeyCode::ENTER; MapKeys[SDL_SCANCODE_PAUSE] = KeyCode::PAUSE;
		MapKeys[SDL_SCANCODE_SCROLLLOCK] = KeyCode::SCROLL; MapKeys[SDL_SCANCODE_TAB] = KeyCode::TAB; MapKeys[SDL_SCANCODE_DELETE] = KeyCode::DEL; MapKeys[SDL_SCANCODE_HOME] = KeyCode::HOME;
		MapKeys[SDL_SCANCODE_END] = KeyCode::END; MapKeys[SDL_SCANCODE_PAGEUP] = KeyCode::PGUP; MapKeys[SDL_SCANCODE_PAGEDOWN] = KeyCode::PGDN; MapKeys[SDL_SCANCODE_INSERT] = KeyCode::INS;
		MapKeys[SDL_SCANCODE_LSHIFT] = KeyCode::L_SHIFT; MapKeys[SDL_SCANCODE_RSHIFT] = KeyCode::R_SHIFT;
		MapKeys[SDL_SCANCODE_LCTRL] = KeyCode::L_CTRL; MapKeys[SDL_SCANCODE_RCTRL] = KeyCode::R_CTRL;
		MapKeys[SDL_SCANCODE_LALT] = KeyCode::L_ALT; MapKeys[SDL_SCANCODE_RALT] = KeyCode::R_ALT;
		MapKeys[SDL_SCANCODE_SPACE] = KeyCode::SPACE;

		MapKeys[SDL_SCANCODE_0] = KeyCode::K0; MapKeys[SDL_SCANCODE_1] = KeyCode::K1; MapKeys[SDL_SCANCODE_2] = KeyCode::K2; MapKeys[SDL_SCANCODE_3] = KeyCode::K3; MapKeys[SDL_SCANCODE_4] = KeyCode::K4;
		MapKeys[SDL_SCANCODE_5] = KeyCode::K5; MapKeys[SDL_SCANCODE_6] = KeyCode::K6; MapKeys[SDL_SCANCODE_7] = KeyCode::K7; MapKeys[SDL_SCANCODE_8] = KeyCode::K8; MapKeys[SDL_SCANCODE_9] = KeyCode::K9;

		MapKeys[SDL_SCANCODE_KP_0] = KeyCode::NP0; MapKeys[SDL_SCANCODE_KP_1] = KeyCode::NP1; MapKeys[SDL_SCANCODE_KP_2] = KeyCode::NP2; MapKeys[SDL_SCANCODE_KP_3] = KeyCode::NP3; MapKeys[SDL_SCANCODE_KP_4] = KeyCode::NP4;
		MapKeys[SDL_SCANCODE_KP_5] = KeyCode::NP5; MapKeys[SDL_SCANCODE_KP_6] = KeyCode::NP6; MapKeys[SDL_SCANCODE_KP_7] = KeyCode::NP7; MapKeys[SDL_SCANCODE_KP_8] = KeyCode::NP8; MapKeys[SDL_SCANCODE_KP_9] = KeyCode::NP9;
		MapKeys[SDL_SCANCODE_KP_MULTIPLY] = KeyCode::NP_MUL; MapKeys[SDL_SCANCODE_KP_PLUS] = KeyCode::NP_PLUS; MapKeys[SDL_SCANCODE_KP_DIVIDE] = KeyCode::NP_DIV; MapKeys[SDL_SCANCODE_KP_MINUS] = KeyCode::NP_MINUS; MapKeys[SDL_SCANCODE_KP_DECIMAL] = KeyCode::NP_DECIMAL;


		MapKeys[SDL_SCANCODE_SEMICOLON] = KeyCode::SEMICOLON;       // On US and UK keyboards this is the ';:' key
		MapKeys[SDL_SCANCODE_SLASH] = KeyCode::SLASH;               // On US and UK keyboards this is the '/?' key
		MapKeys[SDL_SCANCODE_GRAVE] = KeyCode::BACKTICK;            // On US keyboard this is the '~' key
		MapKeys[SDL_SCANCODE_LEFTBRACKET] = KeyCode::LBRACKET;      // On US and UK keyboards this is the '[{' key
		MapKeys[SDL_SCANCODE_BACKSLASH] = KeyCode::BACKSLASH;       // On US keyboard this is '\|' key.
		MapKeys[SDL_SCANCODE_RIGHTBRACKET] = KeyCode::RBRACKET;     // On US and UK keyboards this is the ']}' key
		MapKeys[SDL_SCANCODE_APOSTROPHE] = KeyCode::APOSTROPHE;     // On US keyboard this is the single/double quote key. On UK, this is the single quote/@ symbol key
		MapKeys[SDL_SCANCODE_INTERNATIONAL1] = KeyCode::OEM_8;                      // miscellaneous characters. Varies by keyboard
		MapKeys[SDL_SCANCODE_EQUALS] = KeyCode::EQUALS;             // the '+' key on any keyboard
		MapKeys[SDL_SCANCODE_COMMA] = KeyCode::COMMA;               // the comma key on any keyboard
		MapKeys[SDL_SCANCODE_MINUS] = KeyCode::MINUS;               // the minus key on any keyboard
		MapKeys[SDL_SCANCODE_PERIOD] = KeyCode::PERIOD;             // the period key on any keyboard
		MapKeys[SDL_SCANCODE_CAPSLOCK] = KeyCode::CAPS_LOCK;
	}
}
