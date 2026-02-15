#ifndef RENDERER__SHADER_COMPILER_OPENGL__HPP
#define RENDERER__SHADER_COMPILER_OPENGL__HPP


#include "pch.hpp"


namespace Andromeda::Rendering
{
	class ShaderCompilerOpenGL
	{
	public:
		ShaderCompilerOpenGL();
		~ShaderCompilerOpenGL();

		unsigned int Compile(unsigned int type, const std::string& source);
		unsigned int Link(
			unsigned int vertexShader, 
			unsigned int fragmentShader,
			unsigned int geometryShader = 0
		);

	private:
		bool CheckCompileErrors(unsigned int shader, int type);
		bool CheckLinkErrors(unsigned int program);
	};
}


#endif // RENDERER__SHADER_COMPILER_OPENGL__HPP