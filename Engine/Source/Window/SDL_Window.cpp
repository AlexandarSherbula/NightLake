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
		mSpecs.eventCallback = windowSpec.eventCallback;
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
		SDL_Event sdl_event;
		while (SDL_PollEvent(&sdl_event))
		{
			//ImGui_ImplSDL3_ProcessEvent(&event);

			ProcessEvents(sdl_event, this);
		}
	}

	void ProcessEvents(SDL_Event& sdl_event, SDL3_Window* handle)
	{
		switch (sdl_event.type)
		{
		case SDL_EVENT_WINDOW_RESIZED:
		{
			int32_t width = sdl_event.window.data1;
			int32_t height = sdl_event.window.data2;
			WindowResizeEvent event(width, height);
			handle->GetSpecs().eventCallback(event);
			break;
		}
		case SDL_EVENT_KEY_DOWN:
		{
			KeyPressedEvent event(sdl_event.key.key, true);
			handle->GetSpecs().eventCallback(event);
			Input::GetKeyboard()->SetNewState(Keyboard::MapKeys[sdl_event.key.scancode], true);
			break;
		}
		case SDL_EVENT_KEY_UP:
		{
			KeyReleasedEvent event(sdl_event.key.key);
			handle->GetSpecs().eventCallback(event);
			Input::GetKeyboard()->SetNewState(Keyboard::MapKeys[sdl_event.key.scancode], false);
			break;
		}
		case SDL_EVENT_TEXT_INPUT:
		{
			KeyTypedEvent event(sdl_event.key.key);
			handle->GetSpecs().eventCallback(event);
			break;
		}
		case SDL_EVENT_MOUSE_BUTTON_DOWN:
		{
			MouseButtonPressedEvent event(sdl_event.button.button, sdl_event.button.x, sdl_event.button.y);
			handle->GetSpecs().eventCallback(event);
			Input::GetMouse()->SetNewState(Mouse::MapButtons[sdl_event.button.button], true);
			
			break;
		}
		case SDL_EVENT_MOUSE_BUTTON_UP:
		{
			MouseButtonReleasedEvent event(sdl_event.button.button, sdl_event.button.x, sdl_event.button.y);
			handle->GetSpecs().eventCallback(event);
			Input::GetMouse()->SetNewState(Mouse::MapButtons[sdl_event.button.button], false);
			break;
		}
		case SDL_EVENT_MOUSE_MOTION:
		{
			MouseMovedEvent event(sdl_event.button.x, sdl_event.button.y);
			handle->GetSpecs().eventCallback(event);
			break;
		}
		case SDL_EVENT_MOUSE_WHEEL:
		{
			MouseScrolledEvent event(sdl_event.wheel.x, sdl_event.wheel.y);
			handle->GetSpecs().eventCallback(event);
			break;
		}
		case SDL_EVENT_QUIT:
		{
			WindowCloseEvent event;
			handle->GetSpecs().eventCallback(event);
			break;
		}
		}
	}

}


