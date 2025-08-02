#ifndef RENDERER__SHADER_OPENGL__HPP
#define RENDERER__SHADER_OPENGL__HPP

#include "ShaderProgramOpenGL.hpp"
#include "UniformSetterOpenGL.hpp"
#include "IShader.hpp"
#include "glm/glm.hpp"

namespace Andromeda::Rendering
{
	class ShaderOpenGL
		: public ShaderProgramOpenGL
		, public IShader
	{
	public:
		ShaderOpenGL(const std::string& vertexCode, const std::string& fragmentCode);
		~ShaderOpenGL() = default;

		// Getters
		unsigned int GetProgram() const;
		std::string GetVertexShaderSourceCode() const;
		std::string GetFragmentShaderSourceCode() const;

		// Setters
		void SetVertexShaderProgramSource(const std::string& filepath);
		void SetFragmentShaderProgramSource(const std::string& filepath);

		void Bind() const override;
		void UnBind() const override;

		// Uniform setters
		void SetUniform(const std::string& name, int value) const;
		void SetUniform(const std::string& name, float value) const;
		void SetUniform(const std::string& name, const glm::vec3& vector) const;
		void SetUniform(const std::string& name, const glm::vec4& vector) const;
		void SetUniform(const std::string& name, const glm::mat3& matrix) const;
		void SetUniform(const std::string& name, const glm::mat4& matrix) const;
		void SetUniform(const std::string& name, const std::vector<float>& values) const;
		void SetUniform(const std::string& name, const std::vector<glm::vec3>& vectors) const;
		void SetUniform(const std::string& name, const std::vector<glm::vec4>& vectors) const;

	private:
		UniformSetterOpenGL m_uniformSetter;
	};
}

#endif // RENDERER__SHADER_OPENGL__HPP
