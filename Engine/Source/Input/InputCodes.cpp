#include "nle_pch.hpp"
#include "InputCodes.hpp"

namespace nle
{
	void SetSDL_InputCodes(std::unordered_map<size_t, int8_t>& mapKeys)
	{
		mapKeys[0x00] = Key::NONE;

		mapKeys[SDL_SCANCODE_A] = Key::A; mapKeys[SDL_SCANCODE_B] = Key::B; mapKeys[SDL_SCANCODE_C] = Key::C; mapKeys[SDL_SCANCODE_D] = Key::D; mapKeys[SDL_SCANCODE_E] = Key::E;
		mapKeys[SDL_SCANCODE_F] = Key::F; mapKeys[SDL_SCANCODE_G] = Key::G; mapKeys[SDL_SCANCODE_H] = Key::H; mapKeys[SDL_SCANCODE_I] = Key::I; mapKeys[SDL_SCANCODE_J] = Key::J;
		mapKeys[SDL_SCANCODE_K] = Key::K; mapKeys[SDL_SCANCODE_L] = Key::L; mapKeys[SDL_SCANCODE_M] = Key::M; mapKeys[SDL_SCANCODE_N] = Key::N; mapKeys[SDL_SCANCODE_O] = Key::O;
		mapKeys[SDL_SCANCODE_P] = Key::P; mapKeys[SDL_SCANCODE_Q] = Key::Q; mapKeys[SDL_SCANCODE_R] = Key::R; mapKeys[SDL_SCANCODE_S] = Key::S; mapKeys[SDL_SCANCODE_T] = Key::T;
		mapKeys[SDL_SCANCODE_U] = Key::U; mapKeys[SDL_SCANCODE_V] = Key::V; mapKeys[SDL_SCANCODE_W] = Key::W; mapKeys[SDL_SCANCODE_X] = Key::X; mapKeys[SDL_SCANCODE_E] = Key::Y;
		mapKeys[SDL_SCANCODE_Z] = Key::Z;

		mapKeys[SDL_SCANCODE_F1] = Key::F1; mapKeys[SDL_SCANCODE_F2] = Key::F2; mapKeys[SDL_SCANCODE_F3] = Key::F3; mapKeys[SDL_SCANCODE_F4] = Key::F4;
		mapKeys[SDL_SCANCODE_F5] = Key::F5; mapKeys[SDL_SCANCODE_F6] = Key::F6; mapKeys[SDL_SCANCODE_F7] = Key::F7; mapKeys[SDL_SCANCODE_F8] = Key::F8;
		mapKeys[SDL_SCANCODE_F9] = Key::F9; mapKeys[SDL_SCANCODE_F10] = Key::F10; mapKeys[SDL_SCANCODE_F11] = Key::F11; mapKeys[SDL_SCANCODE_F12] = Key::F12;

		mapKeys[SDL_SCANCODE_DOWN] = Key::DOWN; mapKeys[SDL_SCANCODE_LEFT] = Key::LEFT; mapKeys[SDL_SCANCODE_RIGHT] = Key::RIGHT; mapKeys[SDL_SCANCODE_UP] = Key::UP;

		mapKeys[SDL_SCANCODE_BACKSPACE] = Key::BACK; mapKeys[SDL_SCANCODE_ESCAPE] = Key::ESCAPE; mapKeys[SDL_SCANCODE_RETURN] = Key::ENTER; mapKeys[SDL_SCANCODE_PAUSE] = Key::PAUSE;
		mapKeys[SDL_SCANCODE_SCROLLLOCK] = Key::SCROLL; mapKeys[SDL_SCANCODE_TAB] = Key::TAB; mapKeys[SDL_SCANCODE_DELETE] = Key::DEL; mapKeys[SDL_SCANCODE_HOME] = Key::HOME;
		mapKeys[SDL_SCANCODE_END] = Key::END; mapKeys[SDL_SCANCODE_PAGEUP] = Key::PGUP; mapKeys[SDL_SCANCODE_PAGEDOWN] = Key::PGDN; mapKeys[SDL_SCANCODE_INSERT] = Key::INS;
		mapKeys[SDL_SCANCODE_LSHIFT] = Key::L_SHIFT; mapKeys[SDL_SCANCODE_RSHIFT] = Key::R_SHIFT;
		mapKeys[SDL_SCANCODE_LCTRL] = Key::L_CTRL; mapKeys[SDL_SCANCODE_RCTRL] = Key::R_CTRL;
		mapKeys[SDL_SCANCODE_LALT] = Key::L_ALT; mapKeys[SDL_SCANCODE_RALT] = Key::R_ALT;
		mapKeys[SDL_SCANCODE_SPACE] = Key::SPACE;

		mapKeys[SDL_SCANCODE_0] = Key::K0; mapKeys[SDL_SCANCODE_1] = Key::K1; mapKeys[SDL_SCANCODE_2] = Key::K2; mapKeys[SDL_SCANCODE_3] = Key::K3; mapKeys[SDL_SCANCODE_4] = Key::K4;
		mapKeys[SDL_SCANCODE_5] = Key::K5; mapKeys[SDL_SCANCODE_6] = Key::K6; mapKeys[SDL_SCANCODE_7] = Key::K7; mapKeys[SDL_SCANCODE_8] = Key::K8; mapKeys[SDL_SCANCODE_9] = Key::K9;

		mapKeys[SDL_SCANCODE_KP_0] = Key::NP0; mapKeys[SDL_SCANCODE_KP_1] = Key::NP1; mapKeys[SDL_SCANCODE_KP_2] = Key::NP2; mapKeys[SDL_SCANCODE_KP_3] = Key::NP3; mapKeys[SDL_SCANCODE_KP_4] = Key::NP4;
		mapKeys[SDL_SCANCODE_KP_5] = Key::NP5; mapKeys[SDL_SCANCODE_KP_6] = Key::NP6; mapKeys[SDL_SCANCODE_KP_7] = Key::NP7; mapKeys[SDL_SCANCODE_KP_8] = Key::NP8; mapKeys[SDL_SCANCODE_KP_9] = Key::NP9;
		mapKeys[SDL_SCANCODE_KP_MULTIPLY] = Key::NP_MUL; mapKeys[SDL_SCANCODE_KP_PLUS] = Key::NP_PLUS; mapKeys[SDL_SCANCODE_KP_DIVIDE] = Key::NP_DIV; mapKeys[SDL_SCANCODE_KP_MINUS] = Key::NP_MINUS; mapKeys[SDL_SCANCODE_KP_DECIMAL] = Key::NP_DECIMAL;


		mapKeys[SDL_SCANCODE_SEMICOLON] = Key::SEMICOLON;       // On US and UK keyboards this is the ';:' key
		mapKeys[SDL_SCANCODE_SLASH] = Key::SLASH;               // On US and UK keyboards this is the '/?' key
		mapKeys[SDL_SCANCODE_GRAVE] = Key::BACKTICK;            // On US keyboard this is the '~' key
		mapKeys[SDL_SCANCODE_LEFTBRACKET] = Key::LBRACKET;      // On US and UK keyboards this is the '[{' key
		mapKeys[SDL_SCANCODE_BACKSLASH] = Key::BACKSLASH;       // On US keyboard this is '\|' key.
		mapKeys[SDL_SCANCODE_RIGHTBRACKET] = Key::RBRACKET;     // On US and UK keyboards this is the ']}' key
		mapKeys[SDL_SCANCODE_APOSTROPHE] = Key::APOSTROPHE;     // On US keyboard this is the single/double quote key. On UK, this is the single quote/@ symbol key
		mapKeys[SDL_SCANCODE_INTERNATIONAL1] = Key::OEM_8;                      // miscellaneous characters. Varies by keyboard
		mapKeys[SDL_SCANCODE_EQUALS] = Key::EQUALS;             // the '+' key on any keyboard
		mapKeys[SDL_SCANCODE_COMMA] = Key::COMMA;               // the comma key on any keyboard
		mapKeys[SDL_SCANCODE_MINUS] = Key::MINUS;               // the minus key on any keyboard
		mapKeys[SDL_SCANCODE_PERIOD] = Key::PERIOD;             // the period key on any keyboard
		mapKeys[SDL_SCANCODE_CAPSLOCK] = Key::CAPS_LOCK;
	}

	void SetWin32KeyCodes(std::unordered_map<size_t, int8_t>& mapKeys)
	{
		/*
		mapKeys[0x41] = Key::A; mapKeys[0x42] = Key::B; mapKeys[0x43] = Key::C; mapKeys[0x44] = Key::D; mapKeys[0x45] = Key::E;
		mapKeys[0x46] = Key::F; mapKeys[0x47] = Key::G; mapKeys[0x48] = Key::H; mapKeys[0x49] = Key::I; mapKeys[0x4A] = Key::J;
		mapKeys[0x4B] = Key::K; mapKeys[0x4C] = Key::L; mapKeys[0x4D] = Key::M; mapKeys[0x4E] = Key::N; mapKeys[0x4F] = Key::O;
		mapKeys[0x50] = Key::P; mapKeys[0x51] = Key::Q; mapKeys[0x52] = Key::R; mapKeys[0x53] = Key::S; mapKeys[0x54] = Key::T;
		mapKeys[0x55] = Key::U; mapKeys[0x56] = Key::V; mapKeys[0x57] = Key::W; mapKeys[0x58] = Key::X; mapKeys[0x59] = Key::Y;
		mapKeys[0x5A] = Key::Z;
		*/
	}
}


