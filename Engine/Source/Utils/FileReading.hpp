#pragma once

#include <fstream>
#include <sstream>

#include "Log.hpp"

namespace aio
{
	std::string GetProjectDirectory();

	std::string ReadFromFiles(const std::string& filepath);
}

