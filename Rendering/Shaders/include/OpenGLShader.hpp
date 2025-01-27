#ifndef RENDERER__SHADER__HPP
#define RENDERER__SHADER__HPP


#include "pch.hpp"
//#include "glm/glm.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		class OpenGLShader
		{
		public:
			OpenGLShader();
			OpenGLShader(const std::string& vertexCode, const std::string& fragmentCode);
			~OpenGLShader();

			void Bind() const;
			void UnBind() const;
			//void SetUniform(const std::string& name, float value);
			//void SetUniform(const std::string& name, const glm::mat4& matrix);

			void SetVertexShaderProgramSource(const std::string& filepath);
			std::string GetVertexShaderSourceCode();
			void SetFragmentShaderProgramSource(const std::string& filepath);
			std::string GetFragmentShaderSourceCode();
			unsigned int GetProgram();

		private:
			unsigned int CompileShader(unsigned int type, const std::string& shaderSource);
			unsigned int CreateShaderProgram(const std::string& vertexCode, const std::string& fragmentCode);
			int GetUniformLocation(const std::string& name);
			void CheckCompileErrors(unsigned int shader, int type);
			void CheckProgramErrors(unsigned int program);

			unsigned int m_program;
			std::string m_vertexShaderSourceCode;
			std::string m_fragmentShaderSourceCode;
			std::unordered_map<std::string, int> m_uniformLocationCache;
		};
	}
}


#endif // RENDERER__SHADER__HPP