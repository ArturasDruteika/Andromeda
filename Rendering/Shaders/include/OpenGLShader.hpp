#ifndef RENDERER__SHADER__HPP
#define RENDERER__SHADER__HPP


#include "pch.hpp"
#include "glm/glm.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		class OpenGLShader
		{
		public:
			OpenGLShader(const std::string& vertexCode, const std::string& fragmentCode);
			~OpenGLShader();

			// Getters
			unsigned int GetProgram() const;
			std::string GetVertexShaderSourceCode() const;
			std::string GetFragmentShaderSourceCode() const;
			// Setters
			void SetVertexShaderProgramSource(const std::string& filepath);
			void SetFragmentShaderProgramSource(const std::string& filepath);

			void Bind() const;
			void UnBind() const;
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
			unsigned int CompileShader(unsigned int type, const std::string& shaderSource);
			unsigned int CreateShaderProgram(const std::string& vertexCode, const std::string& fragmentCode);
			int GetUniformLocation(const std::string& name);
			void CheckCompileErrors(unsigned int shader, int type);
			void CheckProgramErrors(unsigned int program);
		
		private:
			unsigned int m_program;
			std::string m_vertexShaderSourceCode;
			std::string m_fragmentShaderSourceCode;
			std::unordered_map<std::string, int> m_uniformLocationCache;
		};
	}
}


#endif // RENDERER__SHADER__HPP