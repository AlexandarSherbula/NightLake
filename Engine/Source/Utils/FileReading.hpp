#pragma once

#include <fstream>
#include <sstream>

#include "Log.hpp"


#define ASSETS_DIRECTORY GetProjectDirectory() + "Sandbox/Assets/"
#define CACHE_DIRECTORY ASSETS_DIRECTORY + "cache/"

namespace aio
{
	std::string GetProjectDirectory();

	std::string ReadFromFiles(const std::string& filepath);

	std::string GetFileName(const std::string& filepath);
}

