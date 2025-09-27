#include "nle_pch.hpp"
#include "Log.hpp"

namespace nle
{
	std::shared_ptr<spdlog::logger> Log::sLogger;

	void Log::Initialize()
	{
		spdlog::set_pattern("%^[%T] %l: %v%$");
		sLogger = spdlog::stdout_color_mt("NightLake");
		sLogger->set_level(spdlog::level::trace);
	}
}

