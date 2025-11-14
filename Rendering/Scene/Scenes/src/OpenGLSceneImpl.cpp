#include "../include/OpenGLSceneImpl.hpp"
#include "../../Support/include/SpecialIndices.hpp"
#include "../../../RenderableObjects/Objects/include/GridOpenGL.hpp"



namespace Andromeda::Rendering
{
	OpenGLScene::OpenGLSceneImpl::OpenGLSceneImpl()
	{
		GridOpenGL* grid = new GridOpenGL(100, m_gridSpacing, 0.05f, PhysicalProperties::Color(0.3f, 0.3f, 0.3f, 1.0f));
		AddObject(static_cast<int>(SpecialIndices::Grid), grid);
	}

	OpenGLScene::OpenGLSceneImpl::~OpenGLSceneImpl() = default;
}
