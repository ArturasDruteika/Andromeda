#include "../include/ShaderSourceManagerOpenGL.hpp"
#include "FileOperations.hpp"


namespace Andromeda::Rendering
{
	ShaderSourceManagerOpenGL::ShaderSourceManagerOpenGL(
		const std::filesystem::path& vertexShaderFilepath,
		const std::filesystem::path& fragmentShaderFilepath,
		bool load
	)
		: m_vertexShaderPath{ vertexShaderFilepath }
		, m_fragmentShaderPath{ fragmentShaderFilepath }
	{
		if (load)
		{
			LoadShaderFromFile(ShaderType::Vertex, vertexShaderFilepath);
			LoadShaderFromFile(ShaderType::Fragment, fragmentShaderFilepath);
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

	const std::string& ShaderSourceManagerOpenGL::GetVertexCode() const
	{
		return m_vertexCode;
	}

	const std::string& ShaderSourceManagerOpenGL::GetFragmentCode() const
	{
		return m_fragmentCode;
	}

	void ShaderSourceManagerOpenGL::LoadShaderFromFile(const ShaderType& shaderType, const std::filesystem::path& filepath)
	{
		if (shaderType == ShaderType::Vertex)
		{
			m_vertexCode = Utils::FileOperations::LoadFileAsString(filepath);
		}
		else if (shaderType == ShaderType::Fragment)
		{
			m_fragmentCode = Utils::FileOperations::LoadFileAsString(filepath);
		}
		else
		{
			throw std::runtime_error("Unsupported shader type for loading from file.");
		}
	}
}
