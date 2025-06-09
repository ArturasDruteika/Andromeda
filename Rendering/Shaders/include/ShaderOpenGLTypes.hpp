#ifndef RENDERER__SHADER_OPENGL_TYPES__HPP
#define RENDERER__SHADER_OPENGL_TYPES__HPP


#include "pch.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		enum class ShaderOpenGLTypes
		{
			RenderableObjects,
			Grid
		};

		struct ShaderDefinition
		{
			ShaderOpenGLTypes type;
			std::string vertexPath;
			std::string fragmentPath;
		};
	}
}


#endif // RENDERER__SHADER_OPENGL_TYPES__HPP