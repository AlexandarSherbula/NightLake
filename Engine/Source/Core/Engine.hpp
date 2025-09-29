#pragma once

#include "Window/Window.hpp"

namespace nle
{
	struct AppSpecifications
	{
		WindowSpecifications windowSpecs;
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
	public:
		Scope<Window> mMainWindow;
	private:
		bool mRunning;
	};
}
