#include "../include/ShaderCompilerOpenGL.hpp"
#include "glad/gl.h"
#include "spdlog/spdlog.h"


namespace Andromeda::Rendering
{
	ShaderCompilerOpenGL::ShaderCompilerOpenGL() = default;

	ShaderCompilerOpenGL::~ShaderCompilerOpenGL() = default;

	unsigned int ShaderCompilerOpenGL::Compile(unsigned int type, const std::string& source)
	{
		unsigned int shader = glCreateShader(type);
		const char* shaderSourcePtr = source.c_str();
		glShaderSource(shader, 1, &shaderSourcePtr, nullptr);
		glCompileShader(shader);
		CheckCompileErrors(shader, type);
		return shader;
	}

	unsigned int ShaderCompilerOpenGL::Link(
		unsigned int vertexShader,
		unsigned int fragmentShader,
		unsigned int geometryShader
	)
	{
		unsigned int program = glCreateProgram();

		if (vertexShader)
			glAttachShader(program, vertexShader);
		if (fragmentShader)
			glAttachShader(program, fragmentShader);
		if (geometryShader)
			glAttachShader(program, geometryShader);

		glLinkProgram(program);

		if (!CheckLinkErrors(program))
		{
			glDeleteProgram(program);
			return 0;
		}

		// Optionally detach after a successful link
		if (vertexShader)
			glDetachShader(program, vertexShader);
		if (fragmentShader)
			glDetachShader(program, fragmentShader);
		if (geometryShader)
			glDetachShader(program, geometryShader);

		return program;
	}

	bool ShaderCompilerOpenGL::CheckCompileErrors(unsigned int shader, int type)
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
			return false;
		}
		return true;
	}

	bool ShaderCompilerOpenGL::CheckLinkErrors(unsigned int program)
	{
		int success;
		glGetProgramiv(program, GL_LINK_STATUS, &success);

		if (!success)
		{
			int length;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
			char* message = static_cast<char*>(alloca(length * sizeof(char)));
			glGetProgramInfoLog(program, length, nullptr, message);
			spdlog::error("Shader program linking error: {}", message);
			glDeleteProgram(program);
			return false;
		}
		return true;
	}
}
