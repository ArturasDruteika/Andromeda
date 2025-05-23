#include "../include/SphereObjectOpenGL.hpp"
#include "../include/SphereObjectOpenGLImpl.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		SphereObjectOpenGL::SphereObjectOpenGL(const Math::Vec3& centerPosition, float radius, const Space::Color& color)
			: m_pSphereObjectOpenGLImpl{ new SphereObjectOpenGL::SphereObjectOpenGLImpl(centerPosition, radius, color) }
		{
		}

		SphereObjectOpenGL::~SphereObjectOpenGL()
		{
			delete m_pSphereObjectOpenGLImpl;
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

		std::vector<Vertex> SphereObjectOpenGL::GetVertices() const
		{
			return m_pSphereObjectOpenGLImpl->GetVertices();
		}

		Math::Mat4 SphereObjectOpenGL::GetModelMatrix() const
		{
			return m_pSphereObjectOpenGLImpl->GetModelMatrix();
		}

		void SphereObjectOpenGL::SetRadius(float radius)
		{
			m_pSphereObjectOpenGLImpl->SetRadius(radius);
		}

		void SphereObjectOpenGL::SetModelMatrix(const Math::Mat4& modelMatrix)
		{
			m_pSphereObjectOpenGLImpl->SetModelMatrix(modelMatrix);
		}

		void SphereObjectOpenGL::UpdateModelMatrix()
		{
			m_pSphereObjectOpenGLImpl->UpdateModelMatrix();
		}

		void SphereObjectOpenGL::SetCenterPosition(const Math::Vec3& position, bool updateModelMatrix)
		{
			m_pSphereObjectOpenGLImpl->SetCenterPosition(position, updateModelMatrix);
		}

		void SphereObjectOpenGL::SetRotation(const Math::Vec3& rotation, bool updateModelMatrix)
		{
			m_pSphereObjectOpenGLImpl->SetRotation(rotation, updateModelMatrix);
		}

		void SphereObjectOpenGL::SetScale(const Math::Vec3& scale, bool updateModelMatrix)
		{
			m_pSphereObjectOpenGLImpl->SetScale(scale, updateModelMatrix);
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

		void SphereObjectOpenGL::Scale(const Math::Vec3& scale)
		{
			m_pSphereObjectOpenGLImpl->Scale(scale);
		}

		float SphereObjectOpenGL::GetRadius() const
		{
			return m_pSphereObjectOpenGLImpl->GetRadius();
		}

		Math::Vec3 SphereObjectOpenGL::GetCenterPosition() const
		{
			return m_pSphereObjectOpenGLImpl->GetCenterPosition();
		}

		Math::Vec3 SphereObjectOpenGL::GetRotation() const
		{
			return m_pSphereObjectOpenGLImpl->GetRotation();
		}

		Math::Vec3 SphereObjectOpenGL::GetScale() const
		{
			return m_pSphereObjectOpenGLImpl->GetScale();
		}
	}
}
