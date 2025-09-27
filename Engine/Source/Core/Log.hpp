#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace nle
{
    class Log
    {
    public:
        static void Initialize();
        static std::shared_ptr<spdlog::logger> sLogger;
    };
}

#if defined (NLE_DEBUG)  || defined(NLE_RELEASE)
#define NLE_LOG_TRACE(...)       nle::Log::sLogger->trace(__VA_ARGS__)
#define NLE_LOG_INFO(...)        nle::Log::sLogger->info(__VA_ARGS__)
#define NLE_LOG_WARN(...)        nle::Log::sLogger->warn(__VA_ARGS__)
#define NLE_LOG_ERROR(...)       nle::Log::sLogger->error(__VA_ARGS__)
#define NLE_LOG_CRITICAL(...)    nle::Log::sLogger->critical(__VA_ARGS__)

#define NLE_ASSERT(x, ...)  if(!(x)) { nle::Log::sLogger->error("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } 
#else
#define NLE_LOG_TRACE(...)
#define NLE_LOG_INFO(...)
#define NLE_LOG_WARN(...)
#define NLE_LOG_ERROR(...)
#define NLE_LOG_CRITICAL(...)

#define NLE_ASSERT(x, ...) x
#endif