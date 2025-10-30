#include "aio_pch.hpp"
#include "FileReading.hpp"

namespace fs = std::filesystem;

namespace aio
{
	const std::string& GetProjectDirectory()
	{
		fs::path projectDir = fs::current_path().parent_path().parent_path();

		return projectDir.generic_string() + "/";
	}

	std::string ReadFromFiles(const std::string& filepath)
	{
		std::string result;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else
		{
			AIO_LOG_ERROR("Could not open file '{0}'", filepath);
		}

		return result;
	}
}


