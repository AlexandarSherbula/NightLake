#include "nle_pch.hpp"
#include "Engine.hpp"

#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_opengl3.h>

namespace nle
{
	static Engine* sInstance = nullptr;

	Engine::Engine()
	{
		
	}

	Engine::Engine(AppSpecifications& appSpecs)
	{
		sInstance = this;

		mRunning = true;
		Log::Initialize();

		mMainWindow = Window::Create({ appSpecs.title, appSpecs.width, appSpecs.height, appSpecs.vSync, NLE_BIND_EVENT_FN(Engine::OnEvent) });
	}

	Engine::~Engine()
	{		
		sInstance = nullptr;
	}

	void Engine::Run()
	{
		mMainWindow->Initialize();

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

		//IMGUI_CHECKVERSION();
		//ImGui::CreateContext();
		//ImGui::StyleColorsDark();
		//ImGuiIO& io = ImGui::GetIO(); (void)io;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//
		//if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		//{
		//	ImGuiStyle& style = ImGui::GetStyle();
		//	style.WindowRounding = 0.0f;
		//	style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		//}

		//ImGui_ImplSDL3_InitForOpenGL(window, glcontext);
		//ImGui_ImplOpenGL3_Init("#version 450 core");

		

		NLE_LOG_INFO("Starting Engine");
		while (mRunning)
		{
			mMainWindow->PollEvents();

			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glBindVertexArray(vao);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glBindVertexArray(0);

			//ImGui_ImplOpenGL3_NewFrame();
			//ImGui_ImplSDL3_NewFrame();
			//ImGui::NewFrame();
			//
			//static bool show = true;
			//ImGui::ShowDemoWindow(&show);
			//
			//ImGuiIO& io = ImGui::GetIO();
			//io.DisplaySize = ImVec2(1280, 720);
			//
			//ImGui::Render();
			//ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			//if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			//{
			//	SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
			//	SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
			//	ImGui::UpdatePlatformWindows();
			//	ImGui::RenderPlatformWindowsDefault();
			//	SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
			//}

			SDL_GL_SwapWindow((SDL_Window*)mMainWindow->GetHandle());
		}

		//ImGui_ImplOpenGL3_Shutdown();
		//ImGui_ImplSDL3_Shutdown();
		//ImGui::DestroyContext();

		
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

	void Engine::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(NLE_BIND_EVENT_FN(Engine::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(NLE_BIND_EVENT_FN(Engine::OnWindowResize));
		dispatcher.Dispatch<KeyPressedEvent>(NLE_BIND_EVENT_FN(Engine::OnKeyPressed));
		dispatcher.Dispatch<KeyReleasedEvent>(NLE_BIND_EVENT_FN(Engine::OnKeyReleased));
		dispatcher.Dispatch<KeyTypedEvent>(NLE_BIND_EVENT_FN(Engine::OnKeyTyped));
		dispatcher.Dispatch<MouseButtonPressedEvent>(NLE_BIND_EVENT_FN(Engine::OnMouseButtonPressed));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(NLE_BIND_EVENT_FN(Engine::OnMouseButtonReleased));
		dispatcher.Dispatch<MouseMovedEvent>(NLE_BIND_EVENT_FN(Engine::OnMouseMoved));
		dispatcher.Dispatch<MouseScrolledEvent>(NLE_BIND_EVENT_FN(Engine::OnMouseScrolled));
	}

	bool Engine::OnWindowClose(WindowCloseEvent& e)
	{
		mRunning = false;
		return true;
	}

	bool Engine::OnWindowResize(WindowResizeEvent& e)
	{
		glViewport(0, 0, e.GetWidth(), e.GetHeight());
		return true;
	}

	bool Engine::OnKeyPressed(KeyPressedEvent& e)
	{
		return true;
	}

	bool Engine::OnKeyReleased(KeyReleasedEvent& e)
	{
		return true;
	}

	bool Engine::OnKeyTyped(KeyTypedEvent& e)
	{
		return true;
	}

	bool Engine::OnMouseButtonPressed(MouseButtonPressedEvent& e)
	{
		return true;
	}

	bool Engine::OnMouseButtonReleased(MouseButtonReleasedEvent& e)
	{
		return true;
	}

	bool Engine::OnMouseMoved(MouseMovedEvent& e)
	{
		return true;
	}

	bool Engine::OnMouseScrolled(MouseScrolledEvent& e)
	{
		return true;
	}
}


