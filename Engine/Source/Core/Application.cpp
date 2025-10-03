#include "nle_pch.hpp"
#include "Application.hpp"

#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_opengl3.h>

namespace nle
{
	static Application* sInstance = nullptr;

	Application::Application()
	{
		
	}

	Application::Application(AppSpecifications& appSpecs)
	{
		sInstance = this;

		mRunning = true;
		Log::Initialize();

		mMainWindow = Window::Create({ appSpecs.title, appSpecs.width, appSpecs.height, appSpecs.vSync, NLE_BIND_EVENT_FN(Application::OnEvent) });
		mMainWindow->Initialize();
	}

	Application::~Application()
	{		
		sInstance = nullptr;
	}

	void Application::Run()
	{

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

		Input::Initialize();

		NLE_LOG_INFO("Starting NightLake Application");
		while (mRunning)
		{
			mMainWindow->PollEvents();
			Input::Scan();

			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glBindVertexArray(vao);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glBindVertexArray(0);

			if (Input::GetKeyboard()->IsHeld(KeyCode::A))
				NLE_LOG_TRACE("A was Held");
			
			if (Input::GetKeyboard()->IsReleased(KeyCode::A))
				NLE_LOG_TRACE("A was released");
			
			if (Input::GetMouse()->IsPressed(L_BUTTON))
				NLE_LOG_TRACE("Left click was pressed.");
			
			if (Input::GetMouse()->IsReleased(L_BUTTON))
				NLE_LOG_TRACE("Left click was released.");

			//NLE_LOG_TRACE("LeftStick x: {0}, y: {1}", Input::GetGamepad().LeftThumbStick().x, Input::GetGamepad().LeftThumbStick().y);
			NLE_LOG_TRACE("LeftTrigger: {0}, RightTrigger: {1}", Input::GetGamepad().LeftTrigger(), Input::GetGamepad().RightTrigger());

			if (Input::GetGamepad().IsHeld(L_STICK_UP))
				NLE_LOG_TRACE("Stick is UP!!");
			if (Input::GetGamepad().IsReleased(L_STICK_UP))
				NLE_LOG_TRACE("Stick is Released!!");
			if (Input::GetGamepad().IsHeld(L_STICK_DOWN))
				NLE_LOG_TRACE("Stick is DOWN!!");
			if (Input::GetGamepad().IsReleased(L_STICK_DOWN))
				NLE_LOG_TRACE("Stick is Released!!");
			
			if (Input::GetGamepad().IsHeld(L_STICK_LEFT))
				NLE_LOG_TRACE("Stick is LEFT!!");
			if (Input::GetGamepad().IsReleased(L_STICK_LEFT))
				NLE_LOG_TRACE("Stick is Released!!");
			if (Input::GetGamepad().IsHeld(L_STICK_RIGHT))
				NLE_LOG_TRACE("Stick is RIGHT!!");
			if (Input::GetGamepad().IsReleased(L_STICK_RIGHT))
				NLE_LOG_TRACE("Stick is Released!!");

			if (Input::GetGamepad().IsHeld(L_STICK_UP))
				NLE_LOG_TRACE("Stick is UP!!");
			if (Input::GetGamepad().IsReleased(L_STICK_UP))
				NLE_LOG_TRACE("Stick is Released!!");
			if (Input::GetGamepad().IsHeld(L_STICK_DOWN))
				NLE_LOG_TRACE("Stick is DOWN!!");
			if (Input::GetGamepad().IsReleased(L_STICK_DOWN))
				NLE_LOG_TRACE("Stick is Released!!");


			if (Input::GetGamepad(1).IsHeld(L_STICK_LEFT))
				NLE_LOG_TRACE("Controller two Stick is LEFT!!");
			if (Input::GetGamepad(1).IsReleased(L_STICK_LEFT))
				NLE_LOG_TRACE("Controller two Stick is Released!!");
			if (Input::GetGamepad(1).IsHeld(L_STICK_RIGHT))
				NLE_LOG_TRACE("Controller two Stick is RIGHT!!");
			if (Input::GetGamepad(1).IsReleased(L_STICK_RIGHT))
				NLE_LOG_TRACE("Controller two Stick is Released!!");

			//NLE_LOG_TRACE(Input::GetMouse()->Wheel().y);

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

			Input::Reset();
		}

		Input::Close();

		//ImGui_ImplOpenGL3_Shutdown();
		//ImGui_ImplSDL3_Shutdown();
		//ImGui::DestroyContext();

		
	}

	void Application::Stop()
	{
		if (mRunning)
			mRunning = false;
	}

	Application& Application::Get()
	{
		NLE_ASSERT(sInstance, "Instance hasn't been made");
		return *sInstance;
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(NLE_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(NLE_BIND_EVENT_FN(Application::OnWindowResize));
		dispatcher.Dispatch<MouseMovedEvent>(NLE_BIND_EVENT_FN(Application::OnMouseMoved));
		dispatcher.Dispatch<MouseScrolledEvent>(NLE_BIND_EVENT_FN(Application::OnMouseScrolled));
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		mRunning = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		glViewport(0, 0, e.GetWidth(), e.GetHeight());
		return true;
	}

	bool Application::OnMouseMoved(MouseMovedEvent& e)
	{		
		Input::GetMouse()->SetPosition(Vector2(e.GetX(), e.GetY()));
		return true;
	}

	bool Application::OnMouseScrolled(MouseScrolledEvent& e)
	{
		Input::GetMouse()->NewMouseWheelState(Vector2(e.GetXOffset(), e.GetYOffset()));
		return true;
	}
}


