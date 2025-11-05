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
		void SetFullScreen() override;

		void SwapBuffers() override;
	private:
		aio::Vector2i mPosition;
		SDLwindowHandler* mHandle;
		
	};
}