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
		PointShadowCubeMap,
		Grid,
	};

	struct ShaderDefinition
	{
		ShaderOpenGLTypes type;
		std::filesystem::path vertexPath{};
		std::filesystem::path fragmentPath{};
		std::filesystem::path geometryPath{};
	};
}


#endif // RENDERER__SHADER_OPENGL_TYPES__HPP