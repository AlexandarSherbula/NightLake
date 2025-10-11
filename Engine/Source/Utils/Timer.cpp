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

	ProfileTimer::ProfileTimer()
	{
		mStartPoint = std::chrono::high_resolution_clock::now();
	}

	ProfileTimer::~ProfileTimer()
	{
		mEndPoint = std::chrono::high_resolution_clock::now();

		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(mStartPoint).time_since_epoch().count();
		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(mEndPoint).time_since_epoch().count();

		auto duration = end - start;
		double ms = duration * 0.001;
		AIO_LOG_TRACE("{0}ms", ms);
	}
}


