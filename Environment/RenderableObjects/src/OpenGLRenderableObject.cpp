#include "../include/OpenGLRenderableObject.hpp"
#include "../include/OpenGLRenderableObjectImpl.hpp"


namespace Andromeda
{
	namespace Environment
	{
		OpenGLRenderableObject::OpenGLRenderableObject(const std::vector<float>& vertices)
			: m_pOpenGLRenderableObjectImpl{ new OpenGLRenderableObject ::OpenGLRenderableObjectImpl(vertices) }
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

		unsigned int OpenGLRenderableObject::GetVertexCount() const
		{
			return m_pOpenGLRenderableObjectImpl->GetVertexCount();
		}

		std::vector<float> OpenGLRenderableObject::GetPosition() const
		{
			return m_pOpenGLRenderableObjectImpl->GetPosition();
		}

		void OpenGLRenderableObject::SetPosition(float x, float y, float z)
		{
			m_pOpenGLRenderableObjectImpl->SetPosition(x, y, z);
		}

		std::vector<float> OpenGLRenderableObject::GetRotation() const
		{
			return m_pOpenGLRenderableObjectImpl->GetRotation();
		}

		void OpenGLRenderableObject::SetRotation(float pitch, float yaw, float roll)
		{
			m_pOpenGLRenderableObjectImpl->SetRotation(pitch, yaw, roll);
		}

		std::vector<float> OpenGLRenderableObject::GetScale() const
		{
			return m_pOpenGLRenderableObjectImpl->GetScale();
		}

		void OpenGLRenderableObject::SetScale(float x, float y, float z)
		{
			m_pOpenGLRenderableObjectImpl->SetScale(x, y, z);
		}
	}
}
