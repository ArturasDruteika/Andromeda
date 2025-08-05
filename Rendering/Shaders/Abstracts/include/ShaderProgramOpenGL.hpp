#ifndef RENDERER__SHADER_PROGRAM_OPENGL__HPP
#define RENDERER__SHADER_PROGRAM_OPENGL__HPP


#include "pch.hpp"


namespace Andromeda::Rendering
{
	class ShaderProgramOpenGL
	{
	public:
		ShaderProgramOpenGL();
		~ShaderProgramOpenGL();

		// Getters
		unsigned int GetProgramId() const;

		void Bind() const;
		void UnBind() const;

	protected:
		void CreateShaderProgram(const std::string& vertexCode, const std::string& fragmentCode);

	protected:
		unsigned int m_programId;
	};
}


#endif // RENDERER__SHADER_PROGRAM_OPENGL__HPP