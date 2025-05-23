#include "../include/CubeObjectOpenGLImpl.hpp"
#include "../../Utils/include/MathUtils.hpp"
#include "Constants.hpp"
#include "Points.hpp"
#include "glad/gl.h"


namespace Andromeda
{
	namespace Rendering
	{
		CubeObjectOpenGL::CubeObjectOpenGLImpl::CubeObjectOpenGLImpl(const Math::Vec3& centerPosition, float halfExtent, const Space::Color& color)
			: m_halfExtent{ halfExtent }
			, RenderableObjectOpenGLBase(
				centerPosition,
				color,
				std::vector {
					Rendering::VertexAttributes{ 0, Space::Point3D::Size(), GL_FLOAT, GL_FALSE, sizeof(Rendering::Vertex), 0 }, // Position
					Rendering::VertexAttributes{ 1, Space::Color::Size(), GL_FLOAT, GL_FALSE, sizeof(Rendering::Vertex), sizeof(Space::Point3D)} // Color
				} 
			)
		{
			ConstructCube(halfExtent, color);
			Init(m_vertices, m_indices);
			UpdateModelMatrix(TransformationType::ALL);
		}

		CubeObjectOpenGL::CubeObjectOpenGLImpl::~CubeObjectOpenGLImpl() = default;

		float CubeObjectOpenGL::CubeObjectOpenGLImpl::GetHalfExtent() const
		{
			return m_halfExtent;
		}

		void CubeObjectOpenGL::CubeObjectOpenGLImpl::SetHalfExtent(float halfExtent)
		{
		}

		void CubeObjectOpenGL::CubeObjectOpenGLImpl::ConstructCube(float halfExtent, const Space::Color& color)
		{
			const float h = halfExtent;
			std::vector<glm::vec3> cubeVerts = {
				{-h, -h, -h}, { h, -h, -h}, { h,  h, -h}, {-h,  h, -h}, // back face
				{-h, -h,  h}, { h, -h,  h}, { h,  h,  h}, {-h,  h,  h}  // front face
			};

			for (const auto& v : cubeVerts)
			{
				m_vertices.push_back(Vertex(Space::Point3D(v.x, v.y, v.z), color));
			}

			m_indices = {
				// back face
				0, 1, 2, 2, 3, 0,
				// front face
				4, 5, 6, 6, 7, 4,
				// left face
				0, 4, 7, 7, 3, 0,
				// right face
				1, 5, 6, 6, 2, 1,
				// bottom face
				0, 1, 5, 5, 4, 0,
				// top face
				3, 2, 6, 6, 7, 3
			};
		}
	}
}
