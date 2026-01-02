#include "../include/RendererOpenGL.hpp"
#include "../../../OpenGL/Renderer/include/RendererOpenGLImpl.hpp"


namespace Andromeda::Rendering
{
	RendererOpenGL::RendererOpenGL()
		: m_pRendererOpenGLImpl{ new RendererOpenGL::RendererOpenGLImpl() }
	{
	}

	RendererOpenGL::~RendererOpenGL()
	{
		delete m_pRendererOpenGLImpl;
	}

	bool RendererOpenGL::IsInitialized() const
	{
		return m_pRendererOpenGLImpl->IsInitialized();
	}

	bool RendererOpenGL::IsGridVisible() const
	{
		return m_pRendererOpenGLImpl->IsGridVisible();
	}

	bool RendererOpenGL::IsIlluminationMode() const
	{
		return m_pRendererOpenGLImpl->IsIlluminationMode();
	}

	unsigned int RendererOpenGL::GetFrameBufferTexture() const
	{
		return m_pRendererOpenGLImpl->GetFrameBufferTexture();
	}

	int RendererOpenGL::GetWidth() const
	{
		return m_pRendererOpenGLImpl->GetWidth();
	}

	int RendererOpenGL::GetHeight() const
	{
		return m_pRendererOpenGLImpl->GetHeight();
	}

	void RendererOpenGL::SetGridVisible(bool visible)
	{
		return m_pRendererOpenGLImpl->SetGridVisible(visible);
	}

	void RendererOpenGL::SetIlluminationMode(bool mode)
	{
		m_pRendererOpenGLImpl->SetIlluminationMode(mode);
	}

	void RendererOpenGL::Init(int width, int height, bool illuminationMode)
	{
		m_pRendererOpenGLImpl->Init(width, height, illuminationMode);
	}

	void RendererOpenGL::DeInit()
	{
		m_pRendererOpenGLImpl->DeInit();
	}

	void RendererOpenGL::RenderFrame(IScene& scene)
	{
		m_pRendererOpenGLImpl->RenderFrame(scene);
	}

	void RendererOpenGL::Resize(int width, int height)
	{
		m_pRendererOpenGLImpl->Resize(width, height);
	}
}
