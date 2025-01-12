#include "../include/RenderableObject.hpp"
#include "../include/RenderableObjectImpl.hpp"


namespace Andromeda
{
	namespace Scene
	{
		OpenGLRenderableObject::OpenGLRenderableObject(const std::vector<float>& vertices)
			: m_pOpenGLRenderableObjectImpl{ new OpenGLRenderableObject ::OpenGLRenderableObjectImpl(vertices) }
		{
		}

		OpenGLRenderableObject::~OpenGLRenderableObject()
		{
			delete m_pOpenGLRenderableObjectImpl;
		}
	}
}
