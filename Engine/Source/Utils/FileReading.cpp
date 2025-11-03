#include "aio_pch.hpp"
#include "FileReading.hpp"



namespace aio
{
	std::filesystem::path GetProjectDirectory()
	{
		return std::filesystem::current_path().parent_path().parent_path();
	}

	std::string ReadFromFiles(const std::filesystem::path& filepath)
	{
		std::string result = "";
		if (std::filesystem::exists(filepath))
		{
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
				AIO_LOG_ERROR("Could not open file '{0}'", filepath.string());
			}
		}
		
		return result;
	}

	std::string GetFileName(const std::filesystem::path& filepath)
	{
		//AIO_ASSERT(std::filesystem::exists(filepath), "Cannot get name from non-existing filepath.");
		auto lastSlash = filepath.string().find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = filepath.string().rfind('.');
		auto count = lastDot == std::string::npos ? filepath.string().size() - lastSlash : lastDot - lastSlash;

		return filepath.string().substr(lastSlash, count);
	}
}


