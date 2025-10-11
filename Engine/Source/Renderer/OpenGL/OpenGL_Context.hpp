#pragma once

#include "Renderer/GraphicsContext.hpp"

#include "Window/SDL_Window.hpp"

namespace aio
{
	class OpenGL_Context : public GraphicsContext
	{
	public:
		OpenGL_Context(SDL_Window* windowHandle);

		virtual void SwapBuffers() override;

		void ImGuiBackendInit() override;
		void ImGuiBackendBegin() override;
		void ImGuiBackendUpdate() override;
		void ImGuiBackendShutDown() override;
	private:
		SDL_Window* mWindowHandle;
		SDL_GLContext mContextHandle;
	};
}