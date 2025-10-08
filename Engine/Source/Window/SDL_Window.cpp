#include "nle_pch.hpp"
#include "SDL_Window.hpp"

#include <backends/imgui_impl_sdl3.h>

namespace nle
{
	static void ProcessEvents(SDL_Event& sdl_event, SDL_Window* window);
	static unsigned int vao;

	SDL_Window::SDL_Window(const WindowSpecifications& windowSpec)
	{
		mSpecs.title = windowSpec.title;
		mSpecs.width = windowSpec.width;
		mSpecs.height = windowSpec.height;
		mSpecs.vSync = windowSpec.vSync;
		mSpecs.eventCallback = windowSpec.eventCallback;

		NLE_ASSERT(SDL_Init(SDL_INIT_VIDEO), "Failed to initalize SDL");
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		mHandle = SDL_CreateWindow("NightLake Engine", 1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
		NLE_ASSERT(mHandle, "Failed to create a window: {0}\n", SDL_GetError());

		mGLContext = SDL_GL_CreateContext(mHandle);
		NLE_ASSERT(mGLContext, "Failed to create GL context");

		SDL_GL_MakeCurrent(mHandle, mGLContext);

		NLE_ASSERT(gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress), "Failed to Init glad.\n");

		float positions[6] = {
		-0.5f, -0.5f,
		0.5f, -0.5f,
		0.0f, 0.5f
		};

		
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
	}

	SDL_Window::~SDL_Window()
	{
		if (mHandle != nullptr)
		{
			SDL_DestroyWindow(mHandle);
			SDL_Quit();
			mHandle = nullptr;
		}
		
	}

	void SDL_Window::Init()
	{
		
	}

	void SDL_Window::PollEvents()
	{
		SDL_Event sdl_event;
		while (SDL_PollEvent(&sdl_event))
		{
			ImGui_ImplSDL3_ProcessEvent(&sdl_event);

			ProcessEvents(sdl_event, this);
		}
	}

	void SDL_Window::Update()
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
	}

	void SDL_Window::SwapChain()
	{
		SDL_GL_SwapWindow(mHandle);
	}

	void ProcessEvents(SDL_Event& sdl_event, SDL_Window* window)
	{
		switch (sdl_event.type)
		{
		case SDL_EVENT_WINDOW_RESIZED:
		case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
		{
			if (sdl_event.window.windowID != SDL_GetWindowID(static_cast<SDL_WindowHandle*>(window->GetHandle())))
				break;

			if (sdl_event.type == SDL_EVENT_WINDOW_RESIZED)
			{
				WindowResizeEvent event(sdl_event.window.data1, sdl_event.window.data2);
				window->GetSpecs().eventCallback(event);
			}

			if (sdl_event.window.windowID == SDL_GetWindowID(static_cast<SDL_WindowHandle*>(window->GetHandle())))
			{
				WindowCloseEvent event;
				window->GetSpecs().eventCallback(event);
			}
			break;
		}
		case SDL_EVENT_KEY_DOWN:
		{
			KeyPressedEvent event(sdl_event.key.key, true);
			window->GetSpecs().eventCallback(event);
			size_t scancode = Keyboard::MapKeys[sdl_event.key.scancode];
			Input::GetKeyboard()->SetNewState(scancode, true);
			break;
		}
		case SDL_EVENT_KEY_UP:
		{
			KeyReleasedEvent event(sdl_event.key.key);
			window->GetSpecs().eventCallback(event);
			Input::GetKeyboard()->SetNewState(Keyboard::MapKeys[sdl_event.key.scancode], false);
			break;
		}
		case SDL_EVENT_TEXT_INPUT:
		{
			KeyTypedEvent event(sdl_event.key.key);
			window->GetSpecs().eventCallback(event);
			break;
		}
		case SDL_EVENT_MOUSE_BUTTON_DOWN:
		{
			MouseButtonPressedEvent event(sdl_event.button.button);
			window->GetSpecs().eventCallback(event);
			Input::GetMouse()->SetNewState(Mouse::MapButtons[sdl_event.button.button], true);
			
			break;
		}
		case SDL_EVENT_MOUSE_BUTTON_UP:
		{
			MouseButtonReleasedEvent event(sdl_event.button.button);
			window->GetSpecs().eventCallback(event);
			Input::GetMouse()->SetNewState(Mouse::MapButtons[sdl_event.button.button], false);
			break;
		}
		case SDL_EVENT_MOUSE_MOTION:
		{
			MouseMovedEvent event(sdl_event.button.x, sdl_event.button.y);
			window->GetSpecs().eventCallback(event);
			break;
		}
		case SDL_EVENT_MOUSE_WHEEL:
		{
			MouseScrolledEvent event(sdl_event.wheel.x, sdl_event.wheel.y);
			window->GetSpecs().eventCallback(event);
			break;
		}
		default:
			Input::ProcessGamePadEvents(sdl_event);
			break;
		}
	}

}


