#include "nle_pch.hpp"
#include "Engine.hpp"

namespace nle
{
	static Engine* sInstance = nullptr;

	Engine::Engine()
	{
		sInstance = this;

		NLE_ASSERT(SDL_Init(SDL_INIT_VIDEO), "Failed to initalize SDL");

		mRunning = true;
		Log::Initialize();
	}

	Engine::~Engine()
	{
		sInstance = nullptr;
	}

	void Engine::Run()
	{
		SDL_Window* window = SDL_CreateWindow("NightLake Engine", 1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
		NLE_ASSERT(window, "Failed to create a window: {0}\n", SDL_GetError());

		SDL_GLContext glcontext = SDL_GL_CreateContext(window);
		NLE_ASSERT(glcontext, "Failed to create GL context");

		SDL_GL_MakeCurrent(window, glcontext);

		SDL_Event event;

		NLE_LOG_INFO("Starting Engine");
		while (mRunning)
		{
			while (SDL_PollEvent(&event)) 
			{
				if (event.type == SDL_EVENT_KEY_DOWN ||
					event.type == SDL_EVENT_QUIT) {
					Stop();
				}
			}

			SDL_GL_SwapWindow(window);
		}
	}

	void Engine::Stop()
	{
		if (mRunning)
			mRunning = false;
	}

	Engine& Engine::Get()
	{
		NLE_ASSERT(sInstance, "Instance hasn't been made");
		return *sInstance;
	}
}


