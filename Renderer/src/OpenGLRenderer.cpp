#include "../include/OpenGLRenderer.hpp"
#include "../include/OpenGLRendererImpl.hpp"


namespace Andromeda
{
	namespace Renderer
	{
		OpenGLRenderer::OpenGLRenderer()
			: m_pOpenGLRendererImpl(new OpenGLRenderer::OpenGLRendererImpl(*this))
		{
		}

		OpenGLRenderer::~OpenGLRenderer()
		{
			delete m_pOpenGLRendererImpl;
		}

		void OpenGLRenderer::Initialize()
		{
			m_pOpenGLRendererImpl->Initialize();
		}

		void OpenGLRenderer::RenderFrame()
		{
			m_pOpenGLRendererImpl->RenderFrame();
		}

		void OpenGLRenderer::Shutdown()
		{
			m_pOpenGLRendererImpl->Shutdown();
		}
	}
}
