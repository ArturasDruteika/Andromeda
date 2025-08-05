#include "../include/OpenGLRenderer.hpp"
#include "../include/OpenGLRendererImpl.hpp"


namespace Andromeda::Rendering
{
	OpenGLRenderer::OpenGLRenderer()
		: m_pOpenGLRendererImpl{ new OpenGLRenderer::OpenGLRendererImpl() }
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

	bool OpenGLRenderer::IsGridVisible() const
	{
		return m_pOpenGLRendererImpl->IsGridVisible();
	}

	bool OpenGLRenderer::IsIlluminationMode() const
	{
		return m_pOpenGLRendererImpl->IsIlluminationMode();
	}

	unsigned int OpenGLRenderer::GetFrameBufferTexture() const
	{
		return m_pOpenGLRendererImpl->GetFrameBufferTexture();
	}

	int OpenGLRenderer::GetWidth() const
	{
		return m_pOpenGLRendererImpl->GetWidth();
	}

	int OpenGLRenderer::GetHeight() const
	{
		return m_pOpenGLRendererImpl->GetHeight();
	}

	void OpenGLRenderer::SetGridVisible(bool visible)
	{
		return m_pOpenGLRendererImpl->SetGridVisible(visible);
	}

	void OpenGLRenderer::SetIlluminationMode(bool mode)
	{
		m_pOpenGLRendererImpl->SetIlluminationMode(mode);
	}

	void OpenGLRenderer::SetCamera(ICamera* camera)
	{
		m_pOpenGLRendererImpl->SetCamera(camera);
	}
		
	void OpenGLRenderer::Init(int width, int height, bool illuminationMode)
	{
		m_pOpenGLRendererImpl->Init(width, height, illuminationMode);
	}

	void OpenGLRenderer::DeInit()
	{
		m_pOpenGLRendererImpl->DeInit();
	}

	void OpenGLRenderer::RenderFrame(IScene& scene)
	{
		m_pOpenGLRendererImpl->RenderFrame(scene);
	}

	void OpenGLRenderer::Resize(int width, int height)
	{
		m_pOpenGLRendererImpl->Resize(width, height);
	}
}
