#include "aio_pch.hpp"
#include "SDL_Window.hpp"

#include "Renderer/OpenGL/OpenGL_Context.hpp"

#include <backends/imgui_impl_sdl3.h>

namespace aio
{
	static void ProcessEvents(SDL_Event& sdl_event, SDLWindow* window);


	SDLWindow::SDLWindow(const WindowSpecifications& windowSpec)
	{
		mSpecs.title = windowSpec.title;
		mSpecs.width = windowSpec.width;
		mSpecs.height = windowSpec.height;
		mSpecs.vSync = windowSpec.vSync;
		mSpecs.isFullScreen = windowSpec.isFullScreen;
		mSpecs.eventCallback = windowSpec.eventCallback;

		AIO_ASSERT(SDL_Init(SDL_INIT_VIDEO), "Failed to initalize SDL");

		mHandle = SDL_CreateWindow(mSpecs.title, mSpecs.width, mSpecs.height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
		AIO_ASSERT(mHandle, "Failed to create a window: {0}\n", SDL_GetError());

		if (mSpecs.isFullScreen)
		{
			// Store current window position and size
			SDL_GetWindowPosition(mHandle, &mPosition.x, &mPosition.y);
			SDL_GetWindowSize(mHandle, &mSpecs.width, &mSpecs.height);

			// Get display mode (resolution, refresh rate, etc.)
			SDL_DisplayID displayId = SDL_GetDisplayForWindow(mHandle);
			SDL_DisplayMode mode;
			if (SDL_GetCurrentDisplayMode(displayId) == 0)
			{
				// Set fullscreen mode to match display
				if (SDL_SetWindowFullscreenMode(mHandle, &mode) != 0)
					AIO_LOG_ERROR("Failed to set fullscreen mode: {0}", SDL_GetError());
			}

			if (SDL_SetWindowFullscreen(mHandle, true) != 0)
				AIO_LOG_ERROR("Failed to enable fullscreen: {0}", SDL_GetError());
		}

		mGraphicsContext = CreateRef<OpenGL_Context>(mHandle);
		mGraphicsContext->SetVSync(mSpecs.vSync);
	}

	SDLWindow::~SDLWindow()
	{
		if (mHandle != nullptr)
		{
			SDL_DestroyWindow(mHandle);
			SDL_Quit();
			mHandle = nullptr;
		}
	}

	void SDLWindow::Init()
	{
	}

	void SDLWindow::PollEvents()
	{
		SDL_Event sdl_event;
		while (SDL_PollEvent(&sdl_event))
		{
			ImGui_ImplSDL3_ProcessEvent(&sdl_event);

			ProcessEvents(sdl_event, this);
		}
	}

	void SDLWindow::Update()
	{
	}
	
	void SDLWindow::SetFullScreen()
	{
		mSpecs.isFullScreen = !mSpecs.isFullScreen;

		if (mSpecs.isFullScreen)
		{
			// Store current window position and size
			SDL_GetWindowPosition(mHandle, &mPosition.x, &mPosition.y);
			SDL_GetWindowSize(mHandle, &mSpecs.width, &mSpecs.height);

			// Get display mode (resolution, refresh rate, etc.)
			SDL_DisplayID displayId = SDL_GetDisplayForWindow(mHandle);
			SDL_DisplayMode mode;
			if (SDL_GetCurrentDisplayMode(displayId) == 0)
			{
				// Set fullscreen mode to match display
				if (SDL_SetWindowFullscreenMode(mHandle, &mode) != 0)
					AIO_LOG_ERROR("Failed to set fullscreen mode: {0}", SDL_GetError());
			}

			if (SDL_SetWindowFullscreen(mHandle, true) != 0)
				AIO_LOG_ERROR("Failed to enable fullscreen: {0}", SDL_GetError());
		}
		else
		{
			// Exit fullscreen
			if (SDL_SetWindowFullscreen(mHandle, false) != 0)
				SDL_Log("Failed to disable fullscreen: %s", SDL_GetError());

			// Restore previous position and size
			SDL_SetWindowPosition(mHandle, mPosition.x, mPosition.y);
			SDL_SetWindowSize(mHandle, mSpecs.width, mSpecs.height);
		}
	}

	void SDLWindow::SwapBuffers()
	{
		mGraphicsContext->SwapChain();
	}

	void ProcessEvents(SDL_Event& sdl_event, SDLWindow* window)
	{
		switch (sdl_event.type)
		{
		case SDL_EVENT_WINDOW_RESIZED:
		case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
		{
			if (sdl_event.window.windowID != SDL_GetWindowID(static_cast<SDLwindowHandler*>(window->GetHandle())))
				break;

			if (sdl_event.type == SDL_EVENT_WINDOW_RESIZED)
			{
				WindowResizeEvent event(sdl_event.window.data1, sdl_event.window.data2);
				window->GetSpecs().eventCallback(event);
				break;
			}

			if (sdl_event.window.windowID == SDL_GetWindowID(static_cast<SDLwindowHandler*>(window->GetHandle())))
			{
				WindowCloseEvent event;
				window->GetSpecs().eventCallback(event);
				break;
			}
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


