#include "../include/CubeObjectOpenGL.hpp"
#include "../include/CubeObjectOpenGLImpl.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		CubeObjectOpenGL::CubeObjectOpenGL(const Math::Vec3& centerPosition, float radius, const Space::Color& color)
			: m_pCubeObjectOpenGLImpl{ new CubeObjectOpenGL::CubeObjectOpenGLImpl(centerPosition, radius, color) }
		{
		}

		CubeObjectOpenGL::~CubeObjectOpenGL()
		{
			delete m_pCubeObjectOpenGLImpl;
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

		std::vector<Vertex> CubeObjectOpenGL::GetVertices() const
		{
			return m_pCubeObjectOpenGLImpl->GetVertices();
		}

		Math::Mat4 CubeObjectOpenGL::GetModelMatrix() const
		{
			return m_pCubeObjectOpenGLImpl->GetModelMatrix();
		}

		void CubeObjectOpenGL::SetModelMatrix(const Math::Mat4& modelMatrix)
		{
			m_pCubeObjectOpenGLImpl->SetModelMatrix(modelMatrix);
		}

		void CubeObjectOpenGL::UpdateModelMatrix()
		{
			m_pCubeObjectOpenGLImpl->UpdateModelMatrix();
		}

		void CubeObjectOpenGL::SetCenterPosition(const Math::Vec3& position, bool updateModelMatrix)
		{
			m_pCubeObjectOpenGLImpl->SetCenterPosition(position, updateModelMatrix);
		}

		void CubeObjectOpenGL::SetRotation(const Math::Vec3& rotation, bool updateModelMatrix)
		{
			m_pCubeObjectOpenGLImpl->SetRotation(rotation, updateModelMatrix);
		}

		void CubeObjectOpenGL::SetScale(const Math::Vec3& scale, bool updateModelMatrix)
		{
			m_pCubeObjectOpenGLImpl->SetScale(scale, updateModelMatrix);
		}

		float CubeObjectOpenGL::GetHalfExtent() const
		{
			return m_pCubeObjectOpenGLImpl->GetHalfExtent();
		}

		Math::Vec3 CubeObjectOpenGL::GetCenterPosition() const
		{
			return m_pCubeObjectOpenGLImpl->GetCenterPosition();
		}

		Math::Vec3 CubeObjectOpenGL::GetRotation() const
		{
			return m_pCubeObjectOpenGLImpl->GetRotation();
		}

		Math::Vec3 CubeObjectOpenGL::GetScale() const
		{
			return m_pCubeObjectOpenGLImpl->GetScale();
		}
	}
}
