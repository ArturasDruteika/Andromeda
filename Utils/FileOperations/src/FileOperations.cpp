#include "../include/FileOperations.hpp"


namespace Andromeda
{
	namespace Utils
	{
		std::string FileOperations::LoadFileAsString(const std::string& filePath)
		{
			std::ifstream file(filePath);
			if (!file.is_open())
			{
				throw std::runtime_error("Failed to open file: " + filePath);
			}

			std::stringstream shaderStream;
			shaderStream << file.rdbuf();
			return shaderStream.str();
		}

		std::string FileOperations::LoadFileAsString(const std::filesystem::path& filePath)
		{
			std::ifstream file(filePath);
			if (!file.is_open())
			{
				throw std::runtime_error("Failed to open file: " + filePath.string());
			}

			std::stringstream shaderStream;
			shaderStream << file.rdbuf();
			return shaderStream.str();
		}
	}
}