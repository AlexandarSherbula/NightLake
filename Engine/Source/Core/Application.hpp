#pragma once

#include "Window/Window.hpp"
#include "Events/Events.hpp"

#include "Input/Input.hpp"

namespace nle
{
	struct AppSpecifications
	{
		std::string title;
		uint32_t width;
		uint32_t height;
		bool vSync = true;
	};

	class Application
	{
	public:
		Application();
		Application(AppSpecifications& appSpecs);
		~Application();

		void Run();
		void Stop();

		static Application& Get();

		void OnEvent(Event& e);
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
		bool OnMouseMoved(MouseMovedEvent& e);
		bool OnMouseScrolled(MouseScrolledEvent& e);
	public:
		Scope<Window> mMainWindow;
	private:
		bool mRunning;
	};
}
