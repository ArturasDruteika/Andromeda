#ifndef RENDERER__SHADER__HPP
#define RENDERER__SHADER__HPP


#include "pch.hpp"


namespace Andromeda
{
	namespace Renderer
	{
		class OpenGLShader
		{
		public:
			OpenGLShader(const std::string& vertexCode, const std::string& fragmentCode);
			~OpenGLShader();

			unsigned int GetProgram();

		private:
			unsigned int CompileShader(unsigned int type, const std::string& shaderSource);
			unsigned int CreateShaderProgram(const std::string& vertexCode, const std::string& fragmentCode);
			void CheckCompileErrors(unsigned int shader, int type);

			unsigned int m_program;
		};
	}
}


#endif // RENDERER__SHADER__HPP