#include "../include/ShaderOpenGL.hpp"
#include "FileOperations.hpp"


namespace Andromeda::Rendering
{
	ShaderOpenGL::ShaderOpenGL(
		const std::filesystem::path& vertexCodeFilePath, 
		const std::filesystem::path& fragmentCodeFilePath,
		const std::filesystem::path& geometryShaderFilepath
	)
		: ShaderSourceManagerOpenGL(vertexCodeFilePath, fragmentCodeFilePath, geometryShaderFilepath, true)
	{
		ShaderProgramOpenGL::CreateShaderProgram(GetVertexCode(), GetFragmentCode());
	}

	void ShaderOpenGL::Bind() const
	{
		ShaderProgramOpenGL::Bind();
	}

	void ShaderOpenGL::UnBind() const
	{
		ShaderProgramOpenGL::UnBind();
	}

	template<typename T>
	void ShaderOpenGL::SetUniform(const std::string& name, const T& value) const
	{
		m_uniformSetter.SetUniform(GetProgramId(), name, value);
	}

	// Explicit template instantiations for allowed types
	template void ShaderOpenGL::SetUniform<int>(const std::string&, const int&) const;
	template void ShaderOpenGL::SetUniform<float>(const std::string&, const float&) const;
	template void ShaderOpenGL::SetUniform<glm::vec3>(const std::string&, const glm::vec3&) const;
	template void ShaderOpenGL::SetUniform<glm::vec4>(const std::string&, const glm::vec4&) const;
	template void ShaderOpenGL::SetUniform<glm::mat3>(const std::string&, const glm::mat3&) const;
	template void ShaderOpenGL::SetUniform<glm::mat4>(const std::string&, const glm::mat4&) const;
	template void ShaderOpenGL::SetUniform<std::vector<float>>(const std::string&, const std::vector<float>&) const;
	template void ShaderOpenGL::SetUniform<std::vector<glm::vec3>>(const std::string&, const std::vector<glm::vec3>&) const;
	template void ShaderOpenGL::SetUniform<std::vector<glm::vec4>>(const std::string&, const std::vector<glm::vec4>&) const;
}
