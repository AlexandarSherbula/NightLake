#pragma once

#include "Window/Window.hpp"

struct SDL_Window;

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
		void EventCallbacks() override;
	private:
		SDL_Window* mHandle;
		SDL_GLContext mGLContext;
	};
}
#endif