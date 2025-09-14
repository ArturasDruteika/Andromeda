#include "../include/UniformSetterOpenGL.hpp"
#include "glad/gl.h"
#include <glm/gtc/type_ptr.hpp>
#include "spdlog/spdlog.h"


namespace Andromeda::Rendering
{
	UniformSetterOpenGL::UniformSetterOpenGL() = default;

	UniformSetterOpenGL::~UniformSetterOpenGL() = default;

	void UniformSetterOpenGL::SetUniform(unsigned int program, const std::string& name, int value) const
	{
		int location = glGetUniformLocation(program, name.c_str());
		if (location != -1)
		{
			glUniform1i(location, value);
		}
		else
		{
			spdlog::warn("Uniform '{}' not found in shader.", name);
		}
	}

	void UniformSetterOpenGL::SetUniform(unsigned int program, const std::string& name, float value) const
	{
		int location = glGetUniformLocation(program, name.c_str());
		if (location == -1)
		{
			spdlog::warn("Uniform '{}' not found in shader.", name);
			return;
		}
		glUniform1f(location, value);
	}


	void UniformSetterOpenGL::SetUniform(unsigned int program, const std::string& name, const glm::vec3& vector) const
	{
		int location = glGetUniformLocation(program, name.c_str());
		if (location == -1)
		{
			spdlog::warn("Uniform '{}' not found in shader.", name);
			return;
		}

		glUniform3f(location, vector.x, vector.y, vector.z);
	}

	void UniformSetterOpenGL::SetUniform(unsigned int program, const std::string& name, const glm::vec4& matrix) const
	{
		int location = glGetUniformLocation(program, name.c_str());
		if (location == -1)
		{
			spdlog::warn("Uniform '{}' not found in shader.", name);
			return;
		}
		glUniform4f(location, matrix.r, matrix.g, matrix.b, matrix.a);
	}

	void UniformSetterOpenGL::SetUniform(unsigned int program, const std::string& name, const glm::mat3& matrix) const
	{
		int location = glGetUniformLocation(program, name.c_str());
		if (location == -1)
		{
			spdlog::warn("Uniform '{}' not found in shader.", name);
			return;
		}

		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void UniformSetterOpenGL::SetUniform(unsigned int program, const std::string& name, const glm::mat4& matrix) const
	{
		int location = glGetUniformLocation(program, name.c_str());
		if (location == -1)
		{
			spdlog::warn("Uniform '{}' not found in shader.", name);
			return;
		}

		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void UniformSetterOpenGL::SetUniform(unsigned int program, const std::string& name, const std::vector<float>& values) const
	{
		for (size_t i = 0; i < values.size(); ++i)
		{
			// construct "name[i]" for each element
			std::string indexedName = name + "[" + std::to_string(i) + "]";
			int location = glGetUniformLocation(program, indexedName.c_str());
			if (location == -1)
			{
				spdlog::warn("Uniform '{}' not found in shader.", indexedName);
				continue;
			}
			// upload single float
			glUniform1f(location, values[i]);
		}
	}

	void UniformSetterOpenGL::SetUniform(unsigned int program, const std::string& name, const std::vector<glm::vec3>& vectors) const
	{
		for (size_t i = 0; i < vectors.size(); ++i)
		{
			std::string indexedName = name + "[" + std::to_string(i) + "]";
			int location = glGetUniformLocation(program, indexedName.c_str());
			if (location == -1)
			{
				spdlog::warn("Uniform '{}' not found in shader.", indexedName);
				continue;
			}
			glUniform3f(location, vectors[i].x, vectors[i].y, vectors[i].z);
		}
	}

	void UniformSetterOpenGL::SetUniform(unsigned int program, const std::string& name, const std::vector<glm::vec4>& vectors) const
	{
		for (size_t i = 0; i < vectors.size(); ++i)
		{
			std::string indexedName = name + "[" + std::to_string(i) + "]";
			int location = glGetUniformLocation(program, indexedName.c_str());
			if (location == -1)
			{
				spdlog::warn("Uniform '{}' not found in shader.", indexedName);
				continue;
			}
			glUniform4f(location, vectors[i].r, vectors[i].g, vectors[i].b, vectors[i].a);
		}
	}

	void UniformSetterOpenGL::SetUniform(unsigned int program, const std::string& name, const std::vector<glm::mat4>& matrices) const
	{
		if (matrices.empty())
			return;

		// Try "name" first, then "name[0]" for array base
		GLint location = glGetUniformLocation(program, name.c_str());
		if (location == -1) 
		{
			std::string name0 = name + "[0]";
			location = glGetUniformLocation(program, name0.c_str());
		}

		if (location == -1) 
		{
			spdlog::warn("Uniform '{}' not found in shader.", name);
			return;
		}

		glUniformMatrix4fv(
			location,
			static_cast<GLsizei>(matrices.size()),
			GL_FALSE, // GLM is column-major -> no transpose
			glm::value_ptr(matrices[0])
		);
	}
}
