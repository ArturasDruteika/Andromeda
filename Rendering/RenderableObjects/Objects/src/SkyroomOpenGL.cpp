#include "../include/SkyroomOpenGL.hpp"
#include "../include/SkyroomOpenGLImpl.hpp"


namespace Andromeda::Rendering
{
	SkyroomOpenGL::SkyroomOpenGL(const Math::Vec3& centerPosition, float halfExtent, const PhysicalProperties::Color& color)
		: m_pSkyroomOpenGLImpl(new SkyroomOpenGLImpl(centerPosition, halfExtent, color))
	{
	}

	SkyroomOpenGL::~SkyroomOpenGL()
	{
		if (m_pSkyroomOpenGLImpl != nullptr)
		{
			delete m_pSkyroomOpenGLImpl;
			m_pSkyroomOpenGLImpl = nullptr;
		}
	}

	// === ILuminous ===
	bool SkyroomOpenGL::IsLuminous() const
	{
		return m_pSkyroomOpenGLImpl->IsLuminous();
	}

	ILightBehavior* SkyroomOpenGL::GetLightBehavior() const
	{
		return m_pSkyroomOpenGLImpl->GetLightBehavior();
	}

	void SkyroomOpenGL::SetLuminousBehavior(ILightBehavior* behavior)
	{
		m_pSkyroomOpenGLImpl->SetLuminousBehavior(behavior);
	}

	// === ITransformable ===
	bool SkyroomOpenGL::StateChanged() const
	{
		return m_pSkyroomOpenGLImpl->StateChanged();
	}

	Math::Vec3 SkyroomOpenGL::GetCenterPosition() const
	{
		return m_pSkyroomOpenGLImpl->GetCenterPosition();
	}

	Math::Mat4 SkyroomOpenGL::GetModelMatrix() const
	{
		return m_pSkyroomOpenGLImpl->GetModelMatrix();
	}

	void SkyroomOpenGL::SetModelMatrix(const Math::Mat4& modelMatrix)
	{
		m_pSkyroomOpenGLImpl->SetModelMatrix(modelMatrix);
	}

	void SkyroomOpenGL::ResetState()
	{
		m_pSkyroomOpenGLImpl->ResetState();
	}

	void SkyroomOpenGL::Translate(const Math::Vec3& translation)
	{
		m_pSkyroomOpenGLImpl->Translate(translation);
	}

	void SkyroomOpenGL::TranslateDelta(const Math::Vec3& translationDelta)
	{
		m_pSkyroomOpenGLImpl->TranslateDelta(translationDelta);
	}

	void SkyroomOpenGL::Rotate(const Math::Vec3& rotation)
	{
		m_pSkyroomOpenGLImpl->Rotate(rotation);
	}

	void SkyroomOpenGL::RotateX(float angle)
	{
		m_pSkyroomOpenGLImpl->RotateX(angle);
	}

	void SkyroomOpenGL::RotateY(float angle)
	{
		m_pSkyroomOpenGLImpl->RotateY(angle);
	}

	void SkyroomOpenGL::RotateZ(float angle)
	{
		m_pSkyroomOpenGLImpl->RotateZ(angle);
	}

	void SkyroomOpenGL::Scale(const Math::Vec3& scale)
	{
		m_pSkyroomOpenGLImpl->Scale(scale);
	}

	// === IGeometry ===
	unsigned int SkyroomOpenGL::GetVerticesCount() const
	{
		return m_pSkyroomOpenGLImpl->GetVerticesCount();
	}

	unsigned int SkyroomOpenGL::GetIndicesCount() const
	{
		return m_pSkyroomOpenGLImpl->GetIndicesCount();
	}

	std::vector<unsigned int> SkyroomOpenGL::GetIndices() const
	{
		return m_pSkyroomOpenGLImpl->GetIndices();
	}

	std::vector<Vertex> SkyroomOpenGL::GetVertices() const
	{
		return m_pSkyroomOpenGLImpl->GetVertices();
	}

	// === IRenderableObject ===
	PhysicalProperties::Color SkyroomOpenGL::GetColor() const
	{
		return m_pSkyroomOpenGLImpl->GetColor();
	}

	void SkyroomOpenGL::SetColor(const PhysicalProperties::Color& color)
	{
		m_pSkyroomOpenGLImpl->SetColor(color);
	}

	// === IRenderableObjectOpenGL ===
	unsigned int SkyroomOpenGL::GetVBO() const
	{
		return m_pSkyroomOpenGLImpl->GetVBO();
	}

	unsigned int SkyroomOpenGL::GetVAO() const
	{
		return m_pSkyroomOpenGLImpl->GetVAO();
	}

	unsigned int SkyroomOpenGL::GetEBO() const
	{
		return m_pSkyroomOpenGLImpl->GetEBO();
	}

	float SkyroomOpenGL::GetHalfExtent() const
	{
		return m_pSkyroomOpenGLImpl->GetHalfExtent();
	}
}
