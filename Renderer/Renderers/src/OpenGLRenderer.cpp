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

        OpenGLRenderer::OpenGLRenderer(const OpenGLRenderer& other)
            : m_pOpenGLRendererImpl{ other.m_pOpenGLRendererImpl }
        {
        }

        OpenGLRenderer& OpenGLRenderer::operator=(const OpenGLRenderer& other)
        {
            if (this != &other)
            {
                delete m_pOpenGLRendererImpl;
                m_pOpenGLRendererImpl = new OpenGLRendererImpl();
            }
            return *this;
        }

        OpenGLRenderer::OpenGLRenderer(OpenGLRenderer&& other) noexcept
            : m_pOpenGLRendererImpl{ other.m_pOpenGLRendererImpl }
        {
            other.m_pOpenGLRendererImpl = nullptr;
        }

        OpenGLRenderer& OpenGLRenderer::operator=(OpenGLRenderer&& other) noexcept
        {
            if (this != &other)
            {
                delete m_pOpenGLRendererImpl;
                m_pOpenGLRendererImpl = other.m_pOpenGLRendererImpl;
                other.m_pOpenGLRendererImpl = nullptr;
            }
            return *this;
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
