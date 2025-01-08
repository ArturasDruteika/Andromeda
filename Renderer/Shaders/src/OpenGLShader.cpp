#include "../include/OpenGLShader.hpp"
#include "glad/gl.h"


namespace Andromeda
{
	namespace Renderer
	{
		OpenGLShader::OpenGLShader(const std::string& vertexCode, const std::string& fragmentCode)
		{
			m_program = CreateShader(vertexCode, fragmentCode);
		}

		OpenGLShader::~OpenGLShader()
		{
			if (m_program != 0)
			{
				glDeleteProgram(m_program);
				m_program = 0;
			}
		}

		unsigned int OpenGLShader::GetProgram()
		{
			return m_program;
		}

		unsigned int OpenGLShader::CompileShader(unsigned int type, const std::string& shaderSource)
		{
			unsigned int shader = glCreateShader(type);
			const char* shaderSourcePtr = shaderSource.c_str();
			glShaderSource(shader, 1, &shaderSourcePtr, nullptr);
			glCompileShader(shader);
			CheckCompileErrors(shader, type);
			return shader;
		}

		unsigned int OpenGLShader::CreateShader(const std::string& vertexCode, const std::string& fragmentCode)
		{
			unsigned int program = glCreateProgram();
			unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexCode);
			unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentCode);

			glAttachShader(program, vertexShader);
			glAttachShader(program, fragmentShader);
			glLinkProgram(program);
			glValidateProgram(program);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			return program;
		}

		void OpenGLShader::CheckCompileErrors(unsigned int shader, int type)
		{
			int success;
			int length;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
				char* message = (char*)_malloca(length * sizeof(char));
				std::string shaderTypeStr = (type == GL_VERTEX_SHADER ? "vertex" : "fragment");
				spdlog::error("Shader compilation error ({}): {}", shaderTypeStr, message);
				glDeleteShader(shader);
			}
			return;
		}
	}
}
