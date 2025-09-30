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
	public:
		Scope<Window> mMainWindow;
	private:
		bool mRunning;
	};
}
