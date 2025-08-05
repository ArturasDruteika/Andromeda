#ifndef RENDERER__SHADER_OPENGL_TYPES__HPP
#define RENDERER__SHADER_OPENGL_TYPES__HPP


#include "pch.hpp"


namespace Andromeda::Rendering
{
	enum class ShaderOpenGLTypes
	{
		RenderableObjects,
		RenderableObjectsLuminous,
		RenderableObjectsNonLuminous,
		ShadowMap,
		Grid,
	};

	struct ShaderDefinition
	{
		ShaderOpenGLTypes type;
		std::filesystem::path vertexPath;
		std::filesystem::path fragmentPath;
	};
}


#endif // RENDERER__SHADER_OPENGL_TYPES__HPP