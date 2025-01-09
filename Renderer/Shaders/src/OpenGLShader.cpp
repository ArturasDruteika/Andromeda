#include "../include/OpenGLShader.hpp"
#include "glad/gl.h"
#include <glm/gtc/type_ptr.hpp>



namespace Andromeda
{
	namespace Renderer
	{
		OpenGLShader::OpenGLShader(const std::string& vertexCode, const std::string& fragmentCode)
		{
			m_program = CreateShaderProgram(vertexCode, fragmentCode);
		}

		OpenGLShader::~OpenGLShader()
		{
			if (m_program != 0)
			{
				glDeleteProgram(m_program);
				m_program = 0;
			}
		}

		void OpenGLShader::Bind() const
		{
			glUseProgram(m_program);
		}

		void OpenGLShader::UnBind() const
		{
			glUseProgram(0);
		}

		void OpenGLShader::SetUniform(const std::string& name, float value)
		{
			int location = GetUniformLocation(name);
			if (location != -1)
			{
				glUniform1f(location, value);
			}
		}

		void OpenGLShader::SetUniform(const std::string& name, const glm::mat4& matrix)
		{
			int location = GetUniformLocation(name);
			if (location != -1)
			{
				glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
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

		unsigned int OpenGLShader::CreateShaderProgram(const std::string& vertexCode, const std::string& fragmentCode)
		{
			unsigned int program = glCreateProgram();
			unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexCode);
			unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentCode);

			glAttachShader(program, vertexShader);
			glAttachShader(program, fragmentShader);
			glLinkProgram(program);
			glValidateProgram(program);
			CheckProgramErrors(program);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			return program;
		}

		int OpenGLShader::GetUniformLocation(const std::string& name)
		{
			if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
			{
				return m_uniformLocationCache[name];
			}

			int location = glGetUniformLocation(m_program, name.c_str());
			if (location == -1)
			{
				spdlog::warn("Uniform '{}' not found or not used in shader.", name);
			}
			else
			{
				m_uniformLocationCache[name] = location;
			}
			return location;
		}

		void OpenGLShader::CheckCompileErrors(unsigned int shader, int type)
		{
			int success;
			int length;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
				char* message = (char*)alloca(length * sizeof(char));
				glGetShaderInfoLog(shader, length, nullptr, message);
				std::string shaderTypeStr = (type == GL_VERTEX_SHADER ? "vertex" : "fragment");
				spdlog::error("Shader compilation error ({}): {}", shaderTypeStr, message);
				glDeleteShader(shader);
			}
			return;
		}

		void OpenGLShader::CheckProgramErrors(unsigned int program)
		{
			int success;
			glGetProgramiv(program, GL_LINK_STATUS, &success);
			if (!success)
			{
				int length;
				glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
				char* message = (char*)alloca(length * sizeof(char));
				glGetProgramInfoLog(program, length, nullptr, message);
				spdlog::error("Shader program linking error: {}", message);
				glDeleteProgram(program);
			}
		}
	}
}
