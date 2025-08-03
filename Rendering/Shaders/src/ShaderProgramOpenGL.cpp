#include "../include/ShaderProgramOpenGL.hpp"
#include "../include/ShaderCompilerOpenGL.hpp"
#include <glad/gl.h>
#include <spdlog/spdlog.h>

namespace Andromeda::Rendering
{
	ShaderProgramOpenGL::ShaderProgramOpenGL()
		: m_programId{ 0 }
	{
	}

	ShaderProgramOpenGL::~ShaderProgramOpenGL()
	{
		if (m_programId != 0)
		{
			glDeleteProgram(m_programId);
			m_programId = 0;
		}
	}

	void ShaderProgramOpenGL::CreateShaderProgram(const std::string& vertexCode, const std::string& fragmentCode)
	{
		ShaderCompilerOpenGL compiler;

		// Compile shaders
		unsigned int vertexShader = compiler.Compile(GL_VERTEX_SHADER, vertexCode);
		unsigned int fragmentShader = compiler.Compile(GL_FRAGMENT_SHADER, fragmentCode);

		// Link program
		m_programId = compiler.Link(vertexShader, fragmentShader);

		// Delete shader objects after linking
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	void ShaderProgramOpenGL::Bind() const
	{
		glUseProgram(m_programId);
	}

	void ShaderProgramOpenGL::UnBind() const
	{
		glUseProgram(0);
	}

	unsigned int ShaderProgramOpenGL::GetProgramId() const
	{
		return m_programId;
	}
}
