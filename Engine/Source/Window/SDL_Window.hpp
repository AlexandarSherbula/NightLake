#pragma once

#include "Window/Window.hpp"

#include "SDL3/SDL.h"

typedef SDL_Window SDL_WindowHandle;

namespace nle
{
	class SDL_Window : public Window
	{
	public:
		SDL_Window(const WindowSpecifications& windowSpec);
		~SDL_Window();
		void Init() override;
		void PollEvents() override;
		void Update() override;

		inline void* GetHandle() const override { return mHandle; }
		inline void* GetContext() const override { return mGLContext; }

		void SwapChain() override;
	private:
		SDL_WindowHandle* mHandle;
		SDL_GLContext mGLContext;
	};
}