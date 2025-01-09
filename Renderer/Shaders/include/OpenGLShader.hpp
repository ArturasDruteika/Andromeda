#ifndef RENDERER__SHADER__HPP
#define RENDERER__SHADER__HPP


#include "pch.hpp"
#include <glm/glm.hpp>


namespace Andromeda
{
	namespace Renderer
	{
		class OpenGLShader
		{
		public:
			OpenGLShader(const std::string& vertexCode, const std::string& fragmentCode);
			~OpenGLShader();

			void Bind() const;
			void UnBind() const;
			void SetUniform(const std::string& name, float value);
			void SetUniform(const std::string& name, const glm::mat4& matrix);

			unsigned int GetProgram();

		private:
			unsigned int CompileShader(unsigned int type, const std::string& shaderSource);
			unsigned int CreateShaderProgram(const std::string& vertexCode, const std::string& fragmentCode);
			int GetUniformLocation(const std::string& name);
			void CheckCompileErrors(unsigned int shader, int type);
			void CheckProgramErrors(unsigned int program);

			unsigned int m_program;
			std::unordered_map<std::string, int> m_uniformLocationCache;
		};
	}
}


#endif // RENDERER__SHADER__HPP