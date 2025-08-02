#include "../include/ShaderOpenGL.hpp"
#include "FileOperations.hpp"
#include "glad/gl.h"
#include <glm/gtc/type_ptr.hpp>


namespace Andromeda:: Rendering
{
	ShaderOpenGL::ShaderOpenGL(const std::string& vertexCode, const std::string& fragmentCode)
		: m_vertexShaderSourceCode{ vertexCode }
		, m_fragmentShaderSourceCode{ fragmentCode }
	{
		m_program = CreateShaderProgram(vertexCode, fragmentCode);
	}

	ShaderOpenGL::~ShaderOpenGL()
	{
		if (m_program != 0)
		{
			glDeleteProgram(m_program);
			m_program = 0;
		}
	}

	unsigned int ShaderOpenGL::GetProgram() const
	{
		return m_program;
	}

	std::string ShaderOpenGL::GetFragmentShaderSourceCode() const
	{
		return m_fragmentShaderSourceCode;
	}

	std::string ShaderOpenGL::GetVertexShaderSourceCode() const
	{
		return m_vertexShaderSourceCode;
	}

	void ShaderOpenGL::SetVertexShaderProgramSource(const std::string& filepath)
	{
		m_vertexShaderSourceCode = Utils::FileOperations::LoadFileAsString(filepath);
	}

	void ShaderOpenGL::SetFragmentShaderProgramSource(const std::string& filepath)
	{
		m_fragmentShaderSourceCode = Utils::FileOperations::LoadFileAsString(filepath);
	}

	void ShaderOpenGL::Bind() const
	{
		glUseProgram(m_program);
	}

	void ShaderOpenGL::UnBind() const
	{
		glUseProgram(0);
	}

	void ShaderOpenGL::SetUniform(const std::string& name, int value) const
	{
		int location = glGetUniformLocation(m_program, name.c_str());
		if (location != -1)
		{
			glUniform1i(location, value);
		}
		else
		{
			spdlog::warn("Uniform '{}' not found in shader.", name);
		}
	}

	void ShaderOpenGL::SetUniform(const std::string& name, float value) const
	{
		int location = glGetUniformLocation(m_program, name.c_str());
		if (location == -1)
		{
			spdlog::warn("Uniform '{}' not found in shader.", name);
			return;
		}
		glUniform1f(location, value);
	}


	void ShaderOpenGL::SetUniform(const std::string& name, const glm::vec3& vector) const
	{
		int location = glGetUniformLocation(m_program, name.c_str());
		if (location == -1)
		{
			spdlog::warn("Uniform '{}' not found in shader.", name);
			return;
		}

		glUniform3f(location, vector.x, vector.y, vector.z);
	}

	void ShaderOpenGL::SetUniform(const std::string& name, const glm::vec4& matrix) const
	{
		int location = glGetUniformLocation(m_program, name.c_str());
		if (location == -1)
		{
			spdlog::warn("Uniform '{}' not found in shader.", name);
			return;
		}
		glUniform4f(location, matrix.r, matrix.g, matrix.b, matrix.a);
	}

	void ShaderOpenGL::SetUniform(const std::string& name, const glm::mat3& matrix) const
	{
		int location = glGetUniformLocation(m_program, name.c_str());
		if (location == -1)
		{
			spdlog::warn("Uniform '{}' not found in shader.", name);
			return;
		}

		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void ShaderOpenGL::SetUniform(const std::string& name, const glm::mat4& matrix) const
	{
		int location = glGetUniformLocation(m_program, name.c_str());
		if (location == -1)
		{
			spdlog::warn("Uniform '{}' not found in shader.", name);
			return;
		}

		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void ShaderOpenGL::SetUniform(const std::string& name, const std::vector<float>& values) const
	{
		for (size_t i = 0; i < values.size(); ++i)
		{
			// construct "name[i]" for each element
			std::string indexedName = name + "[" + std::to_string(i) + "]";
			int location = glGetUniformLocation(m_program, indexedName.c_str());
			if (location == -1)
			{
				spdlog::warn("Uniform '{}' not found in shader.", indexedName);
				continue;
			}
			// upload single float
			glUniform1f(location, values[i]);
		}
	}

	void ShaderOpenGL::SetUniform(const std::string& name, const std::vector<glm::vec3>& vectors) const
	{
		for (size_t i = 0; i < vectors.size(); ++i)
		{
			std::string indexedName = name + "[" + std::to_string(i) + "]";
			int location = glGetUniformLocation(m_program, indexedName.c_str());
			if (location == -1)
			{
				spdlog::warn("Uniform '{}' not found in shader.", indexedName);
				continue;
			}
			glUniform3f(location, vectors[i].x, vectors[i].y, vectors[i].z);
		}
	}

	void ShaderOpenGL::SetUniform(const std::string& name, const std::vector<glm::vec4>& vectors) const
	{
		for (size_t i = 0; i < vectors.size(); ++i)
		{
			std::string indexedName = name + "[" + std::to_string(i) + "]";
			int location = glGetUniformLocation(m_program, indexedName.c_str());
			if (location == -1)
			{
				spdlog::warn("Uniform '{}' not found in shader.", indexedName);
				continue;
			}
			glUniform4f(location, vectors[i].r, vectors[i].g, vectors[i].b, vectors[i].a);
		}
	}

	unsigned int ShaderOpenGL::CompileShader(unsigned int type, const std::string& shaderSource)
	{
		unsigned int shader = glCreateShader(type);
		const char* shaderSourcePtr = shaderSource.c_str();
		glShaderSource(shader, 1, &shaderSourcePtr, nullptr);
		glCompileShader(shader);
		CheckCompileErrors(shader, type);
		return shader;
	}

	unsigned int ShaderOpenGL::CreateShaderProgram(const std::string& vertexCode, const std::string& fragmentCode)
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

	int ShaderOpenGL::GetUniformLocation(const std::string& name)
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

	void ShaderOpenGL::CheckCompileErrors(unsigned int shader, int type)
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

	void ShaderOpenGL::CheckProgramErrors(unsigned int program)
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
