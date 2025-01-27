#include "../include/OpenGLRenderer.hpp"
#include "../include/OpenGLRendererImpl.hpp"
#include "FileOperations.hpp"


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

		void OpenGLRenderer::RenderFrame(const Rendering::OpenGLScene& scene, int width, int height)
		{
			m_pOpenGLRendererImpl->RenderFrame(scene, width, height);
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
	}
}
