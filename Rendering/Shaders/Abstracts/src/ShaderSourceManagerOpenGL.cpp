#include "../include/ShaderSourceManagerOpenGL.hpp"
#include "FileOperations.hpp"
#include "spdlog/spdlog.h"


namespace Andromeda::Rendering
{
	ShaderSourceManagerOpenGL::ShaderSourceManagerOpenGL(
		const std::filesystem::path& vertexShaderFilepath,
		const std::filesystem::path& fragmentShaderFilepath,
		const std::filesystem::path& geometryShaderFilepath,
		bool load
	)
		: m_vertexShaderPath{ vertexShaderFilepath }
		, m_fragmentShaderPath{ fragmentShaderFilepath }
		, m_geometryShaderPath{ geometryShaderFilepath }
	{
		if (load)
		{
			LoadShaderFromFile(ShaderType::Vertex, vertexShaderFilepath);
			LoadShaderFromFile(ShaderType::Fragment, fragmentShaderFilepath);
			if (!geometryShaderFilepath.empty())
				LoadShaderFromFile(ShaderType::Fragment, geometryShaderFilepath);
		}
	}

	ShaderSourceManagerOpenGL::~ShaderSourceManagerOpenGL() = default;

	const std::filesystem::path& ShaderSourceManagerOpenGL::GetVertexShaderPath() const
	{
		return m_vertexShaderPath;
	}

	const std::filesystem::path& ShaderSourceManagerOpenGL::GetFragmentShaderPath() const
	{
		return m_fragmentShaderPath;
	}

	const std::filesystem::path& ShaderSourceManagerOpenGL::GetGeometryShaderPath() const
	{
		return m_geometryShaderPath;
	}

	const std::string& ShaderSourceManagerOpenGL::GetVertexCode() const
	{
		return m_vertexCode;
	}

	const std::string& ShaderSourceManagerOpenGL::GetFragmentCode() const
	{
		return m_fragmentCode;
	}

	const std::string& ShaderSourceManagerOpenGL::GetGeometryCode() const
	{
		return m_geometryCode;
	}

	void ShaderSourceManagerOpenGL::LoadShaderFromFile(const ShaderType& shaderType, const std::filesystem::path& filepath)
	{
		std::error_code ec;
		if (filepath.empty() || !std::filesystem::exists(filepath, ec) || !std::filesystem::is_regular_file(filepath, ec))
		{
			spdlog::error("Shader file not found or not a regular file: {}", filepath.string());
			throw std::runtime_error("Shader file not found: " + filepath.string());
		}

		const std::string code = Utils::FileOperations::LoadFileAsString(filepath);

		switch (shaderType)
		{
			case ShaderType::Vertex:
			{
				m_vertexCode = code;
				break;
			}
			case ShaderType::Fragment:
			{
				m_fragmentCode = code;
				break;
			}
			// Optional: if you add geometry support
			case ShaderType::Geometry:
			{
				m_geometryCode = code;
				break;
			}
			default:
			{
				throw std::runtime_error("Unsupported shader type for loading from file.");
			}
		}

	}
}
