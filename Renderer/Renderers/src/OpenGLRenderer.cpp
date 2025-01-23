#include "../include/OpenGLRenderer.hpp"
#include "../include/OpenGLRendererImpl.hpp"


namespace Andromeda
{
	namespace Renderer
	{
		OpenGLRenderer::OpenGLRenderer()
            : m_pOpenGLRendererImpl{ new OpenGLRenderer::OpenGLRendererImpl()}
		{
		}

		OpenGLRenderer::~OpenGLRenderer()
		{
			delete m_pOpenGLRendererImpl;
		}

		void OpenGLRenderer::Init(const char* name)
		{
			m_pOpenGLRendererImpl->Init(name);
		}

		void OpenGLRenderer::DeInit()
		{
			m_pOpenGLRendererImpl->DeInit();
		}

		void OpenGLRenderer::RenderFrame(const Environment::OpenGLScene& scene)
		{
			m_pOpenGLRendererImpl->RenderFrame(scene);
		}

		void OpenGLRenderer::ResizeViewport(int width, int height)
		{
			m_pOpenGLRendererImpl->ResizeViewport(width, height);
		}

		bool OpenGLRenderer::IsInitialized() const
		{
			return m_pOpenGLRendererImpl->IsInitialized();
		}

		unsigned int OpenGLRenderer::GetFrameBufferObject()
		{
			return m_pOpenGLRendererImpl->GetFrameBufferObject();
		}

		unsigned int OpenGLRenderer::GetFrameBufferObjectTexture()
		{
			return m_pOpenGLRendererImpl->GetFrameBufferObjectTexture();
		}
	}
}
