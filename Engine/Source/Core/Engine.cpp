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
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		SDL_Window* window = SDL_CreateWindow("NightLake Engine", 1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
		NLE_ASSERT(window, "Failed to create a window: {0}\n", SDL_GetError());

		SDL_GLContext glcontext = SDL_GL_CreateContext(window);
		NLE_ASSERT(glcontext, "Failed to create GL context");

		SDL_GL_MakeCurrent(window, glcontext);

		NLE_ASSERT(gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress), "Failed to initialize glad.\n");

		float positions[6] = {
		-0.5f, -0.5f,
		0.5f, -0.5f,
		0.0f, 0.5f
		};

		unsigned int vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		unsigned int vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, positions, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

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

			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glBindVertexArray(vao);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glBindVertexArray(0);

			SDL_GL_SwapWindow(window);
		}

		SDL_DestroyWindow(window);
		SDL_Quit();
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


