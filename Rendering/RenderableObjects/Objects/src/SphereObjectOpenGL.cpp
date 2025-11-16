#include "../include/SphereObjectOpenGL.hpp"
#include "../include/SphereObjectOpenGLImpl.hpp"


namespace Andromeda::Rendering
{
	SphereObjectOpenGL::SphereObjectOpenGL(const Math::Vec3& centerPosition, float radius, const PhysicalProperties::Color& color)
		: m_pSphereObjectOpenGLImpl{ new SphereObjectOpenGL::SphereObjectOpenGLImpl(centerPosition, radius, color) }
	{
	}

	SphereObjectOpenGL::~SphereObjectOpenGL()
	{
		delete m_pSphereObjectOpenGLImpl;
	}

	bool SphereObjectOpenGL::IsLuminous() const
	{
		return m_pSphereObjectOpenGLImpl->IsLuminous();
	}

	bool SphereObjectOpenGL::StateChanged() const
	{
		return m_pSphereObjectOpenGLImpl->StateChanged();
	}

	unsigned int SphereObjectOpenGL::GetVBO() const
	{
		return m_pSphereObjectOpenGLImpl->GetVBO();
	}

	unsigned int SphereObjectOpenGL::GetVAO() const
	{
		return m_pSphereObjectOpenGLImpl->GetVAO();
	}

	unsigned int SphereObjectOpenGL::GetEBO() const
	{
		return m_pSphereObjectOpenGLImpl->GetEBO();
	}

	unsigned int SphereObjectOpenGL::GetVertexCount() const
	{
		return m_pSphereObjectOpenGLImpl->GetVertexCount();
	}

	unsigned int SphereObjectOpenGL::GetIndexCount() const
	{
		return m_pSphereObjectOpenGLImpl->GetIndexCount();
	}

	const std::vector<unsigned int>& SphereObjectOpenGL::GetIndices() const
	{
		return m_pSphereObjectOpenGLImpl->GetIndices();
	}

	const std::vector<PhysicalProperties::Vertex>& SphereObjectOpenGL::GetVertices() const
	{
		return m_pSphereObjectOpenGLImpl->GetVertices();
	}

	Math::Vec3 SphereObjectOpenGL::GetCenterPosition() const
	{
		return m_pSphereObjectOpenGLImpl->GetCenterPosition();
	}

	Math::Mat4 SphereObjectOpenGL::GetModelMatrix() const
	{
		return m_pSphereObjectOpenGLImpl->GetModelMatrix();
	}

	PhysicalProperties::Color SphereObjectOpenGL::GetColor() const
	{
		return m_pSphereObjectOpenGLImpl->GetColor();
	}

	PhysicalProperties::ILightBehavior* SphereObjectOpenGL::GetLightBehavior() const
	{
		return m_pSphereObjectOpenGLImpl->GetLightBehavior();
	}

	void SphereObjectOpenGL::SetModelMatrix(const Math::Mat4& modelMatrix)
	{
		m_pSphereObjectOpenGLImpl->SetModelMatrix(modelMatrix);
	}

	void SphereObjectOpenGL::SetLuminousBehavior(PhysicalProperties::ILightBehavior* behavior)
	{
		m_pSphereObjectOpenGLImpl->SetLuminousBehavior(behavior);
	}

	void SphereObjectOpenGL::ResetState()
	{
		m_pSphereObjectOpenGLImpl->ResetState();
	}

	void SphereObjectOpenGL::Translate(const Math::Vec3& translation)
	{
		m_pSphereObjectOpenGLImpl->Translate(translation);
	}

	void SphereObjectOpenGL::TranslateDelta(const Math::Vec3& translationDelta)
	{
		m_pSphereObjectOpenGLImpl->TranslateDelta(translationDelta);
	}

	void SphereObjectOpenGL::Rotate(const Math::Vec3& rotation)
	{
		m_pSphereObjectOpenGLImpl->Rotate(rotation);
	}

	void SphereObjectOpenGL::RotateX(float angle)
	{
		m_pSphereObjectOpenGLImpl->RotateX(angle);
	}

	void SphereObjectOpenGL::RotateY(float angle)
	{
		m_pSphereObjectOpenGLImpl->RotateY(angle);
	}

	void SphereObjectOpenGL::RotateZ(float angle)
	{
		m_pSphereObjectOpenGLImpl->RotateZ(angle);
	}

	void SphereObjectOpenGL::Scale(const Math::Vec3& scale)
	{
		m_pSphereObjectOpenGLImpl->Scale(scale);
	}

	void SphereObjectOpenGL::SetColor(const PhysicalProperties::Color& color)
	{
	}

	float SphereObjectOpenGL::GetRadius() const
	{
		return m_pSphereObjectOpenGLImpl->GetRadius();
	}

	void SphereObjectOpenGL::SetRadius(float radius)
	{
		m_pSphereObjectOpenGLImpl->SetRadius(radius);
	}
}
