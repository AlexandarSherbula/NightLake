#pragma once

#include "Window/Window.hpp"
#include "Events/Events.hpp"

namespace nle
{
	struct AppSpecifications
	{
		std::string title;
		uint32_t width;
		uint32_t height;
		bool vSync = true;
	};

	class Engine
	{
	public:
		Engine();
		Engine(AppSpecifications& appSpecs);
		~Engine();

		void Run();
		void Stop();

		static Engine& Get();

		void OnEvent(Event& e);
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
		bool OnKeyPressed(KeyPressedEvent& e);
		bool OnKeyReleased(KeyReleasedEvent& e);
		bool OnKeyTyped(KeyTypedEvent& e);
		bool OnMouseButtonPressed(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleased(MouseButtonReleasedEvent& e);
		bool OnMouseMoved(MouseMovedEvent& e);
		bool OnMouseScrolled(MouseScrolledEvent& e);
	public:
		Scope<Window> mMainWindow;
	private:
		bool mRunning;
	};
}
