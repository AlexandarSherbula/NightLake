#include "nle_pch.hpp"
#include "Engine.hpp"

namespace nle
{
	static Engine* sInstance = nullptr;

	Engine::Engine()
	{
		sInstance = this;

		mRunning = true;
		Log::Initialize();
	}

	Engine::~Engine()
	{
		sInstance = nullptr;
	}

	void Engine::Run()
	{
		NLE_LOG_INFO("NightLake Engine begins\n");
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
		NLE_ASSERT(sInstance, "Instance hasn't been made");
		return *sInstance;
	}
}


