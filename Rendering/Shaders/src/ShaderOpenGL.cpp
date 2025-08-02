#include "../include/ShaderOpenGL.hpp"
#include "FileOperations.hpp"

namespace Andromeda::Rendering
{
	ShaderOpenGL::ShaderOpenGL(const std::string& vertexCode, const std::string& fragmentCode)
		: ShaderProgramOpenGL()
	{
		CreateShaderProgram(vertexCode, fragmentCode);
	}

	unsigned int ShaderOpenGL::GetProgram() const
	{
		return GetId();  // From ShaderProgramOpenGL
	}

	std::string ShaderOpenGL::GetVertexShaderSourceCode() const
	{
		return GetVertexCode();  // From ShaderSourceManagerOpenGL
	}

	std::string ShaderOpenGL::GetFragmentShaderSourceCode() const
	{
		return GetFragmentCode();  // From ShaderSourceManagerOpenGL
	}

	void ShaderOpenGL::SetVertexShaderProgramSource(const std::string& filepath)
	{
		LoadVertexShaderFromFile(filepath);  // From ShaderSourceManagerOpenGL
	}

	void ShaderOpenGL::SetFragmentShaderProgramSource(const std::string& filepath)
	{
		LoadFragmentShaderFromFile(filepath);  // From ShaderSourceManagerOpenGL
	}

	void ShaderOpenGL::Bind() const
	{
		ShaderProgramOpenGL::Bind();
	}

	void ShaderOpenGL::UnBind() const
	{
		ShaderProgramOpenGL::UnBind();
	}

	void ShaderOpenGL::SetUniform(const std::string& name, int value) const
	{
		m_uniformSetter.SetUniform(GetId(), name, value);
	}

	void ShaderOpenGL::SetUniform(const std::string& name, float value) const
	{
		m_uniformSetter.SetUniform(GetId(), name, value);
	}

	void ShaderOpenGL::SetUniform(const std::string& name, const glm::vec3& vector) const
	{
		m_uniformSetter.SetUniform(GetId(), name, vector);
	}

	void ShaderOpenGL::SetUniform(const std::string& name, const glm::vec4& vector) const
	{
		m_uniformSetter.SetUniform(GetId(), name, vector);
	}

	void ShaderOpenGL::SetUniform(const std::string& name, const glm::mat3& matrix) const
	{
		m_uniformSetter.SetUniform(GetId(), name, matrix);
	}

	void ShaderOpenGL::SetUniform(const std::string& name, const glm::mat4& matrix) const
	{
		m_uniformSetter.SetUniform(GetId(), name, matrix);
	}

	void ShaderOpenGL::SetUniform(const std::string& name, const std::vector<float>& values) const
	{
		m_uniformSetter.SetUniform(GetId(), name, values);
	}

	void ShaderOpenGL::SetUniform(const std::string& name, const std::vector<glm::vec3>& vectors) const
	{
		m_uniformSetter.SetUniform(GetId(), name, vectors);
	}

	void ShaderOpenGL::SetUniform(const std::string& name, const std::vector<glm::vec4>& vectors) const
	{
		m_uniformSetter.SetUniform(GetId(), name, vectors);
	}
}
