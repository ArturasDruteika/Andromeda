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

		void OpenGLRenderableObject::SetPosition(float x, float y, float z)
		{
			m_pOpenGLRenderableObjectImpl->SetPosition(x, y, z);
		}

		std::vector<float> OpenGLRenderableObject::GetPosition()
		{
			return m_pOpenGLRenderableObjectImpl->GetPosition();
		}

		void OpenGLRenderableObject::SetRotation(float pitch, float yaw, float roll)
		{
			m_pOpenGLRenderableObjectImpl->SetRotation(pitch, yaw, roll);
		}

		std::vector<float> OpenGLRenderableObject::GetRotation()
		{
			return m_pOpenGLRenderableObjectImpl->GetRotation();
		}

		void OpenGLRenderableObject::SetScale(float x, float y, float z)
		{
			m_pOpenGLRenderableObjectImpl->SetScale(x, y, z);
		}

		std::vector<float> OpenGLRenderableObject::GetScale()
		{
			return m_pOpenGLRenderableObjectImpl->GetScale();
		}
	}
}
