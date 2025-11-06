#include "aio_pch.hpp"
#include "Timer.hpp"

namespace aio
{
	float AppTimer::sAppTime = 0.0f;
	std::chrono::duration<float> AppTimer::sDeltaTime;
	std::chrono::time_point<std::chrono::high_resolution_clock> AppTimer::sCurrentTime;
	std::chrono::time_point<std::chrono::high_resolution_clock> AppTimer::sLastFrame;

	void AppTimer::Start()
	{
		sCurrentTime = std::chrono::high_resolution_clock::now();
		sLastFrame = std::chrono::high_resolution_clock::now();
	}

	void AppTimer::Update()
	{
		sCurrentTime = std::chrono::high_resolution_clock::now();
		sDeltaTime = sCurrentTime - sLastFrame;
		sLastFrame = sCurrentTime;
		sAppTime += sDeltaTime.count();
	}
}


