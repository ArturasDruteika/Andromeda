#include "../include/SceneOpenGLImpl.hpp"
#include "../../Support/include/SpecialIndices.hpp"
#include "../../../RenderableObjects/Objects/include/GridOpenGL.hpp"



namespace Andromeda::Rendering
{
	SceneOpenGL::SceneOpenGLImpl::SceneOpenGLImpl()
	{
		GridOpenGL* grid = new GridOpenGL(100, m_gridSpacing, 0.05f, Space::Color(0.3f, 0.3f, 0.3f, 1.0f));
		AddObject(static_cast<int>(SpecialIndices::Grid), grid);
	}

	SceneOpenGL::SceneOpenGLImpl::~SceneOpenGLImpl() = default;
}
