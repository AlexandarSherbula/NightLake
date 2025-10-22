#include "aio_pch.hpp"
#include "OpenGL_Context.hpp"

#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_opengl3.h>

namespace aio
{
	OpenGL_Context::OpenGL_Context(SDLwindowHandler* windowHandle)
	{
		mWindowHandle = windowHandle;

		mContextHandle = SDL_GL_CreateContext(mWindowHandle);
		AIO_ASSERT(mContextHandle, "Failed to create GL context");

		SDL_GL_MakeCurrent(mWindowHandle, mContextHandle);
		AIO_ASSERT(gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress), "Failed to init glad.\n");

		
	}

	void OpenGL_Context::SwapChain()
	{
		SDL_GL_SetSwapInterval((int32_t)mVSync);
		SDL_GL_SwapWindow(mWindowHandle);
	}

	void OpenGL_Context::ImGuiBackendInit()
	{
		ImGui_ImplSDL3_InitForOpenGL(mWindowHandle, mContextHandle);
		ImGui_ImplOpenGL3_Init("#version 450 core");

		ImGui_ImplSDL3_SetGamepadMode(ImGui_ImplSDL3_GamepadMode_Manual);
	}

	void OpenGL_Context::ImGuiBackendBegin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL3_NewFrame();
		ImGui::NewFrame();
	}

	void OpenGL_Context::ImGuiBackendUpdate()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			SDLwindowHandler* backup_current_window = SDL_GL_GetCurrentWindow();
			SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
		}
	}

	void OpenGL_Context::ImGuiBackendShutDown()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplSDL3_Shutdown();
		ImGui::DestroyContext();
	}
}