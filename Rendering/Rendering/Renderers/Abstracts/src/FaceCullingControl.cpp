#include "../include/FaceCullingControlOpenGL.hpp"


namespace Andromeda::Rendering
{
	FaceCullingControlOpenGL::FaceCullingControlOpenGL()
		: m_isFaceCullingEnabled{ false }
		, m_isBackFaceCullingEnabled{ false }
	{
	}

	FaceCullingControlOpenGL::~FaceCullingControlOpenGL() = default;

	bool FaceCullingControlOpenGL::IsFaceCullingEnabled() const
	{
		return m_isFaceCullingEnabled;
	}

	bool FaceCullingControlOpenGL::IsBackFaceCullingEnabled() const
	{
		return m_isBackFaceCullingEnabled;
	}

	void FaceCullingControlOpenGL::EnableFaceCulling(unsigned int face, unsigned int winding)
	{
		glEnable(GL_CULL_FACE);
		glCullFace(face);
		glFrontFace(winding);
		m_isFaceCullingEnabled = true;
		m_isBackFaceCullingEnabled = (face == GL_BACK);
	}

	void FaceCullingControlOpenGL::DisableFaceCulling()
	{
		glDisable(GL_CULL_FACE);
		glFrontFace(GL_CCW);
		m_isFaceCullingEnabled = false;
	}
}
