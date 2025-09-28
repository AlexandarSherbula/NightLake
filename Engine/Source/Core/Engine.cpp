#include "nle_pch.hpp"
#include "Engine.hpp"

#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_opengl3.h>

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

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGuiStyle& style = ImGui::GetStyle();
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		ImGui_ImplSDL3_InitForOpenGL(window, glcontext);
		ImGui_ImplOpenGL3_Init("#version 450 core");

		SDL_Event event;

		NLE_LOG_INFO("Starting Engine");
		while (mRunning)
		{
			while (SDL_PollEvent(&event)) 
			{
				ImGui_ImplSDL3_ProcessEvent(&event);
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

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplSDL3_NewFrame();
			ImGui::NewFrame();

			static bool show = true;
			ImGui::ShowDemoWindow(&show);

			ImGuiIO& io = ImGui::GetIO();
			io.DisplaySize = ImVec2(1280, 720);		

			// Rendering
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
				SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();
				SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
			}


			

			SDL_GL_SwapWindow(window);
		}

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplSDL3_Shutdown();
		ImGui::DestroyContext();

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


