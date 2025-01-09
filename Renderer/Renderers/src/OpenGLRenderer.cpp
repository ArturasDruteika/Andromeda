#include "../include/OpenGLRenderer.hpp"
#include "../include/OpenGLRendererImpl.hpp"


namespace Andromeda
{
	namespace Renderer
	{
		OpenGLRenderer::OpenGLRenderer()
            : m_pOpenGLRendererImpl{ new OpenGLRenderer::OpenGLRendererImpl(*this)}
		{
		}

		OpenGLRenderer::~OpenGLRenderer()
		{
		}

        bool OpenGLRenderer::IsInitialized() const
        {
            return m_pOpenGLRendererImpl->IsInitialized();
        }

		void OpenGLRenderer::Initialize(GLADloadfunc load)
		{
			m_pOpenGLRendererImpl->Initialize(load);
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
