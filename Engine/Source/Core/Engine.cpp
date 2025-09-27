#include "nle_pch.hpp"
#include "Engine.hpp"

namespace nle
{
	static Engine* sInstance = nullptr;

	Engine::Engine()
	{
		mRunning = true;
		sInstance = this;
	}

	Engine::~Engine()
	{
		sInstance = nullptr;
	}

	void Engine::Run()
	{
		std::cout << "NightLake Engine begins\n";
		while (mRunning)
		{

		}
	}

	void Engine::Stop()
	{
		if (mRunning)
			mRunning = false;
	}

	Engine& Engine::Get()
	{
		if (sInstance)
			return *sInstance;
	}
}


