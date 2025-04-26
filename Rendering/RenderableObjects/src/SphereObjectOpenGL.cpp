#include "../include/SphereObjectOpenGL.hpp"

namespace Andromeda
{
	namespace Rendering
	{
		SphereObjectOpenGL::SphereObjectOpenGL()
		{
		}

		SphereObjectOpenGL::~SphereObjectOpenGL()
		{
		}

		unsigned int SphereObjectOpenGL::GetVBO() const
		{
			return 0;
		}

		unsigned int SphereObjectOpenGL::GetVAO() const
		{
			return 0;
		}

		unsigned int SphereObjectOpenGL::GetEBO() const
		{
			return 0;
		}

		unsigned int SphereObjectOpenGL::GetVertexCount() const
		{
			return 0;
		}

		std::vector<Space::Vertex> SphereObjectOpenGL::GetVertices() const
		{
			return std::vector<Space::Vertex>();
		}

		Math::Mat4 SphereObjectOpenGL::GetModelMatrix() const
		{
			return Math::Mat4();
		}

		void SphereObjectOpenGL::SetModelMatrix(const Math::Mat4& modelMatrix)
		{
		}

		void SphereObjectOpenGL::UpdateModelMatrix()
		{
		}

		void SphereObjectOpenGL::SetPosition(const Math::Vec3& position, bool updateModelMatrix)
		{
		}

		void SphereObjectOpenGL::SetRotation(const Math::Vec3& rotation, bool updateModelMatrix)
		{
		}

		void SphereObjectOpenGL::SetScale(const Math::Vec3& scale, bool updateModelMatrix)
		{
		}

		void SphereObjectOpenGL::ConstructSphere(float radius)
		{
		}
	}
}
