#include "../include/CubeObjectOpenGL.hpp"
#include "../include/CubeObjectOpenGLImpl.hpp"


namespace Andromeda::Rendering
{
	CubeObjectOpenGL::CubeObjectOpenGL(const Math::Vec3& centerPosition, float radius, const Space::Color& color)
		: m_pCubeObjectOpenGLImpl{ new CubeObjectOpenGL::CubeObjectOpenGLImpl(centerPosition, radius, color) }
	{
	}

	CubeObjectOpenGL::~CubeObjectOpenGL()
	{
		delete m_pCubeObjectOpenGLImpl;
	}

	bool CubeObjectOpenGL::IsLuminous() const
	{
		return m_pCubeObjectOpenGLImpl->IsLuminous();
	}

	bool CubeObjectOpenGL::StateChanged() const
	{
		return m_pCubeObjectOpenGLImpl->StateChanged();
	}

	unsigned int CubeObjectOpenGL::GetVBO() const
	{
		return m_pCubeObjectOpenGLImpl->GetVBO();
	}

	unsigned int CubeObjectOpenGL::GetVAO() const
	{
		return m_pCubeObjectOpenGLImpl->GetVAO();
	}

	unsigned int CubeObjectOpenGL::GetEBO() const
	{
		return m_pCubeObjectOpenGLImpl->GetEBO();
	}

	unsigned int CubeObjectOpenGL::GetVertexCount() const
	{
		return m_pCubeObjectOpenGLImpl->GetVertexCount();
	}

	unsigned int CubeObjectOpenGL::GetIndexCount() const
	{
		return m_pCubeObjectOpenGLImpl->GetIndexCount();
	}

	const std::vector<unsigned int>& CubeObjectOpenGL::GetIndices() const
	{
		return m_pCubeObjectOpenGLImpl->GetIndices();
	}

	const std::vector<Space::Vertex>& CubeObjectOpenGL::GetVertices() const
	{
		return m_pCubeObjectOpenGLImpl->GetVertices();
	}

	Math::Vec3 CubeObjectOpenGL::GetCenterPosition() const
	{
		return m_pCubeObjectOpenGLImpl->GetCenterPosition();
	}

	Math::Mat4 CubeObjectOpenGL::GetModelMatrix() const
	{
		return m_pCubeObjectOpenGLImpl->GetModelMatrix();
	}

	Space::Color CubeObjectOpenGL::GetColor() const
	{
		return m_pCubeObjectOpenGLImpl->GetColor();
	}

	Space::ILightBehavior* CubeObjectOpenGL::GetLightBehavior() const
	{
		return m_pCubeObjectOpenGLImpl->GetLightBehavior();
	}

	void CubeObjectOpenGL::SetModelMatrix(const Math::Mat4& modelMatrix)
	{
		m_pCubeObjectOpenGLImpl->SetModelMatrix(modelMatrix);
	}

	void CubeObjectOpenGL::SetLuminousBehavior(Space::ILightBehavior* behavior)
	{
		m_pCubeObjectOpenGLImpl->SetLuminousBehavior(behavior);
	}

	void CubeObjectOpenGL::ResetState()
	{
		m_pCubeObjectOpenGLImpl->ResetState();
	}

	void CubeObjectOpenGL::Translate(const Math::Vec3& translation)
	{
		m_pCubeObjectOpenGLImpl->Translate(translation);
	}

	void CubeObjectOpenGL::TranslateDelta(const Math::Vec3& translationDelta)
	{
		m_pCubeObjectOpenGLImpl->TranslateDelta(translationDelta);
	}

	void CubeObjectOpenGL::Rotate(const Math::Vec3& rotation)
	{
		m_pCubeObjectOpenGLImpl->Rotate(rotation);
	}

	void CubeObjectOpenGL::RotateX(float angle)
	{
		m_pCubeObjectOpenGLImpl->RotateX(angle);
	}

	void CubeObjectOpenGL::RotateY(float angle)
	{
		m_pCubeObjectOpenGLImpl->RotateY(angle);
	}

	void CubeObjectOpenGL::RotateZ(float angle)
	{
		m_pCubeObjectOpenGLImpl->RotateZ(angle);
	}

	void CubeObjectOpenGL::Scale(const Math::Vec3& scale)
	{
		m_pCubeObjectOpenGLImpl->Scale(scale);
	}

	void CubeObjectOpenGL::SetColor(const Space::Color& color)
	{
	}

	float CubeObjectOpenGL::GetHalfExtent() const
	{
		return m_pCubeObjectOpenGLImpl->GetHalfExtent();
	}
}
