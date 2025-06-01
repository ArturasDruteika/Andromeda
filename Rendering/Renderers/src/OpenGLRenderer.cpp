#include "../include/OpenGLRenderer.hpp"
#include "../include/OpenGLRendererImpl.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		OpenGLRenderer::OpenGLRenderer()
			: m_pOpenGLRendererImpl{ new OpenGLRenderer::OpenGLRendererImpl() }
		{
		}

		OpenGLRenderer::~OpenGLRenderer()
		{
			delete m_pOpenGLRendererImpl;
		}

		void OpenGLRenderer::Init(int width, int height)
		{
			m_pOpenGLRendererImpl->Init(width, height);
		}

		void OpenGLRenderer::DeInit()
		{
			m_pOpenGLRendererImpl->DeInit();
		}

		void OpenGLRenderer::RenderFrame(const Rendering::OpenGLScene& scene)
		{
			m_pOpenGLRendererImpl->RenderFrame(scene);
		}

		bool OpenGLRenderer::IsInitialized() const
		{
			return m_pOpenGLRendererImpl->IsInitialized();
		}

		bool OpenGLRenderer::IsGridVisible() const
		{
			return m_pOpenGLRendererImpl->IsGridVisible();
		}

		unsigned int OpenGLRenderer::GetFrameBufferObject() const
		{
			return m_pOpenGLRendererImpl->GetFrameBufferObject();
		}

		unsigned int OpenGLRenderer::GetFrameBufferObjectTexture() const
		{
			return m_pOpenGLRendererImpl->GetFrameBufferObjectTexture();
		}

		unsigned int OpenGLRenderer::GetDepthBuffer() const
		{
			return m_pOpenGLRendererImpl->GetDepthBuffer();
		}

		int OpenGLRenderer::GetWidth() const
		{
			return m_pOpenGLRendererImpl->GetWidth();
		}

		int OpenGLRenderer::GetHeight() const
		{
			return m_pOpenGLRendererImpl->GetHeight();
		}

		float OpenGLRenderer::GetAmbientStrength() const
		{
			return m_pOpenGLRendererImpl->GetAmbientStrength();
		}

		float OpenGLRenderer::GetSpecularStrength() const
		{
			return m_pOpenGLRendererImpl->GetSpecularStrength();
		}

		float OpenGLRenderer::GetShininess() const
		{
			return m_pOpenGLRendererImpl->GetShininess();
		}

		void OpenGLRenderer::Resize(int width, int height)
		{
			m_pOpenGLRendererImpl->Resize(width, height);
		}

		void OpenGLRenderer::SetGridVisible(bool visible)
		{
			return m_pOpenGLRendererImpl->SetGridVisible(visible);
		}

		void OpenGLRenderer::SetCamera(Camera* camera)
		{
			m_pOpenGLRendererImpl->SetCamera(camera);
		}

		void OpenGLRenderer::SetAmbientStrength(float ambientStrength)
		{
			m_pOpenGLRendererImpl->SetAmbientStrength(ambientStrength);
		}

		void OpenGLRenderer::SetSpecularStrength(float specularStrength)
		{
			m_pOpenGLRendererImpl->SetSpecularStrength(specularStrength);
		}

		void OpenGLRenderer::SetShininess(float shininess)
		{
			m_pOpenGLRendererImpl->SetShininess(shininess);
		}
	}
}
