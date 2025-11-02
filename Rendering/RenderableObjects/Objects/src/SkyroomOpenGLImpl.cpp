#include "../include/SkyroomOpenGLImpl.hpp"
#include "glad/gl.h"


namespace Andromeda::Rendering
{
	SkyroomOpenGL::SkyroomOpenGLImpl::SkyroomOpenGLImpl(const Math::Vec3& centerPosition, const Space::Color& color)
		: RenderableObjectOpenGL(
			centerPosition, 
			color,
			std::vector {
				VertexAttributes{ 0, Space::Point3D::Size(), GL_FLOAT, GL_FALSE, sizeof(Vertex), 0 }, // Position
				VertexAttributes{ 1, Space::Color::Size(), GL_FLOAT, GL_FALSE, sizeof(Vertex), sizeof(Space::Point3D)} // Color
			}
		)
	{
	}

	SkyroomOpenGL::SkyroomOpenGLImpl::~SkyroomOpenGLImpl() = default;
}


