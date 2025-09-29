#include "nle_pch.hpp"
#include "SDL_Window.hpp"

namespace nle
{
	SDL3_Window::SDL3_Window(const WindowSpecifications& windowSpec)
	{
		mSpecs.title = windowSpec.title;
		mSpecs.width = windowSpec.width;
		mSpecs.height = windowSpec.height;
		mSpecs.vSync = windowSpec.vSync;
	}

	SDL3_Window::~SDL3_Window()
	{
		if (mHandle != nullptr)
		{
			SDL_DestroyWindow(mHandle);
			SDL_Quit();
			mHandle = nullptr;
		}
		
	}

	void SDL3_Window::Initialize()
	{
		NLE_ASSERT(SDL_Init(SDL_INIT_VIDEO), "Failed to initalize SDL");
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		mHandle = SDL_CreateWindow("NightLake Engine", 1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
		NLE_ASSERT(mHandle, "Failed to create a window: {0}\n", SDL_GetError());

		mGLContext = SDL_GL_CreateContext(mHandle);
		NLE_ASSERT(mGLContext, "Failed to create GL context");

		SDL_GL_MakeCurrent(mHandle, mGLContext);
	}

	void SDL3_Window::PollEvents()
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			//ImGui_ImplSDL3_ProcessEvent(&event);
			if (event.type == SDL_EVENT_KEY_DOWN ||
				event.type == SDL_EVENT_QUIT)
			{
				if (event.key.key == SDLK_A)
				{
					std::cout << "A key pressed (layout-dependent)" << std::endl;
				}

				if (event.key.key == SDLK_ESCAPE)
				{
					SDL_DestroyWindow(mHandle);
					SDL_Quit();
					mHandle = nullptr;
				}
			}
		}
	}

	void SDL3_Window::EventCallbacks()
	{
	}


}


