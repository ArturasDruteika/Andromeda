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

        bool OpenGLRenderer::IsInitialized() const
        {
            return m_pOpenGLRendererImpl->IsInitialized();
        }

		void OpenGLRenderer::Initialize(const char* name)
		{
			m_pOpenGLRendererImpl->Initialize(name);
		}

		void OpenGLRenderer::RenderFrame(const Environment::OpenGLScene& scene)
		{
			m_pOpenGLRendererImpl->RenderFrame(scene);
		}

		void OpenGLRenderer::Shutdown()
		{
			m_pOpenGLRendererImpl->Shutdown();
		}
	}
}
