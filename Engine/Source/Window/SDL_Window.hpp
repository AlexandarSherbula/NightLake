#pragma once

#include "Window/Window.hpp"

#include "SDL3/SDL.h"

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

		void SwapChain() override;
	private:
		SDL_Window* mHandle;
		
	};
}