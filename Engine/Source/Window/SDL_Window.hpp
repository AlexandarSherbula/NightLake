#pragma once

#include "Window/Window.hpp"

#include "SDL3/SDL.h"

typedef SDL_Window SDLwindowHandler;

namespace aio
{
	class SDLWindow : public Window
	{
	public:
		SDLWindow(const WindowSpecifications& windowSpec);
		~SDLWindow();
		void Init() override;
		void PollEvents() override;
		void Update() override;

		inline void* GetHandle() const override { return mHandle; }

		void SwapBuffers() override;
	private:
		SDLwindowHandler* mHandle;
		
	};
}