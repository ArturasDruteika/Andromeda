#include "../include/ShaderSourceManagerOpenGL.hpp"
#include "FileOperations.hpp"


namespace Andromeda::Rendering
{
	ShaderSourceManagerOpenGL::ShaderSourceManagerOpenGL(
		const std::string& vertexShaderFilepath,
		const std::string& fragmentShaderFilepath,
		bool load
	)
		: m_vertexShaderPath{ vertexShaderFilepath }
		, m_fragmentShaderPath{ fragmentShaderFilepath }
	{
		if (load)
		{
			LoadVertexShaderFromFile(vertexShaderFilepath);
			LoadFragmentShaderFromFile(fragmentShaderFilepath);
		}
	}

	ShaderSourceManagerOpenGL::~ShaderSourceManagerOpenGL() = default;

	const std::string& ShaderSourceManagerOpenGL::GetVertexShaderPath() const
	{
		return m_vertexShaderPath;
	}

	const std::string& ShaderSourceManagerOpenGL::GetFragmentShaderPath() const
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

	void ShaderSourceManagerOpenGL::LoadVertexShaderFromFile(const std::string& filepath)
	{
		m_vertexCode = Utils::FileOperations::LoadFileAsString(filepath);
	}

	void ShaderSourceManagerOpenGL::LoadFragmentShaderFromFile(const std::string& filepath)
	{
		m_fragmentCode = Utils::FileOperations::LoadFileAsString(filepath);
	}
}
