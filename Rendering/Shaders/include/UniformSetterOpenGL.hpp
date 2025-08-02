#ifndef RENDERER__UNIFORM_SETTER_OPENGL__HPP
#define RENDERER__UNIFORM_SETTER_OPENGL__HPP


#include "pch.hpp"
#include "glm/glm.hpp"


namespace Andromeda::Rendering
{
	class UniformSetterOpenGL
	{
	public:
		UniformSetterOpenGL();
		~UniformSetterOpenGL();

		void SetUniform(unsigned int program, const std::string& name, int value) const;
		void SetUniform(unsigned int program, const std::string& name, float value) const;
		void SetUniform(unsigned int program, const std::string& name, const glm::vec3& vector) const;
		void SetUniform(unsigned int program, const std::string& name, const glm::vec4& vector) const;
		void SetUniform(unsigned int program, const std::string& name, const glm::mat3& matrix) const;
		void SetUniform(unsigned int program, const std::string& name, const glm::mat4& matrix) const;
		void SetUniform(unsigned int program, const std::string& name, const std::vector<float>& values) const;
		void SetUniform(unsigned int program, const std::string& name, const std::vector<glm::vec3>& vectors) const;
		void SetUniform(unsigned int program, const std::string& name, const std::vector<glm::vec4>& vectors) const;
	};
}


#endif // RENDERER__UNIFORM_SETTER_OPENGL__HPP