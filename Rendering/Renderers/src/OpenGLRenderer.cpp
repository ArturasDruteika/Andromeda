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

		unsigned int OpenGLRenderer::GetFrameBufferObject() const
		{
			return m_pOpenGLRendererImpl->GetFrameBufferObject();
		}

		unsigned int OpenGLRenderer::GetFrameBufferObjectTexture() const
		{
			return m_pOpenGLRendererImpl->GetFrameBufferObjectTexture();
		}

		int OpenGLRenderer::GetWidth() const
		{
			return m_pOpenGLRendererImpl->GetWidth();
		}

		int OpenGLRenderer::GetHeight() const
		{
			return m_pOpenGLRendererImpl->GetHeight();
		}

		void OpenGLRenderer::Resize(int width, int height)
		{
			m_pOpenGLRendererImpl->Resize(width, height);
		}
	}
}
