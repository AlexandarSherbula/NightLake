#pragma once

#include <fstream>
#include <sstream>

#include "Log.hpp"

namespace aio
{
	const std::string& GetProjectDirectory();

	std::string ReadFromFiles(const std::string& filepath);
}

