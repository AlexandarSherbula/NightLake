#pragma once

#include "Window/Window.hpp"

#include "SDL3/SDL.h"

#if defined(NLE_API_OPENGL)
namespace nle
{
	class SDL3_Window : public Window
	{
	public:
		SDL3_Window(const WindowSpecifications& windowSpec);
		~SDL3_Window();
		void Initialize() override;
		void PollEvents() override;

		inline void* GetHandle() const override { return mHandle; }
	private:
		SDL_Window* mHandle;
		SDL_GLContext mGLContext;
	};

	void ProcessEvents(SDL_Event& sdl_event, SDL3_Window* handle);
}
#endif