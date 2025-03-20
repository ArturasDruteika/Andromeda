#include "../include/OpenGLRenderableObject.hpp"
#include "../include/OpenGLRenderableObjectImpl.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		OpenGLRenderableObject::OpenGLRenderableObject(
			const std::vector<Vertex>& vertices,
			const std::vector<unsigned int>& indices, 
			const VertexLayout& layout
		)
			: m_pOpenGLRenderableObjectImpl{ new OpenGLRenderableObject::OpenGLRenderableObjectImpl{ vertices, indices, layout} }
		{
		}

		OpenGLRenderableObject::~OpenGLRenderableObject()
		{
			delete m_pOpenGLRenderableObjectImpl;
		}

		unsigned int OpenGLRenderableObject::GetVBO() const
		{
			return m_pOpenGLRenderableObjectImpl->GetVBO();
		}

		unsigned int OpenGLRenderableObject::GetVAO() const
		{
			return m_pOpenGLRenderableObjectImpl->GetVAO();
		}

		unsigned int OpenGLRenderableObject::GetEBO() const
		{
			return m_pOpenGLRenderableObjectImpl->GetEBO();
		}

		unsigned int OpenGLRenderableObject::GetVertexCount() const
		{
			return m_pOpenGLRenderableObjectImpl->GetVertexCount();
		}

		std::vector<Vertex> OpenGLRenderableObject::GetVertices() const
		{
			return m_pOpenGLRenderableObjectImpl->GetVertices();
		}
	}
}
