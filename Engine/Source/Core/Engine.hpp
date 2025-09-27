#pragma once

namespace nle
{
	class Engine
	{
	public:
		Engine();
		~Engine();

		void Run();
		void Stop();

		static Engine& Get();
	private:
		bool mRunning;
	};
}
