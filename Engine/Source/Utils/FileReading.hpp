#pragma once

#include <fstream>
#include <sstream>

#include "Log.hpp"

#if defined(AIO_DEBUG)
	#define ASSETS_DIRECTORY GetProjectDirectory() + "Sandbox/Assets/"
#else
	#define ASSETS_DIRECTORY "Assets/"
#endif

#define CACHE_DIRECTORY ASSETS_DIRECTORY "cache/"

namespace aio
{
	std::string GetProjectDirectory();

	std::string ReadFromFiles(const std::string& filepath);

	std::string GetFileName(const std::string& filepath);
}

