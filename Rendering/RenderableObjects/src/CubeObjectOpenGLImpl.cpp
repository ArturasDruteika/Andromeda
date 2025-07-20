#include "../include/CubeObjectOpenGLImpl.hpp"
#include "../../Utils/include/MathUtils.hpp"
#include "Constants.hpp"
#include "Points.hpp"
#include "glad/gl.h"


namespace Andromeda
{
	namespace Rendering
	{
		struct CubeFace
		{
			glm::vec3 normal;
			std::array<glm::vec3, 4> vertices;
		};


		CubeObjectOpenGL::CubeObjectOpenGLImpl::CubeObjectOpenGLImpl(const Math::Vec3& centerPosition, float halfExtent, const Space::Color& color)
			: m_halfExtent{ halfExtent }
			, RenderableObjectOpenGLBase(
				centerPosition,
				color,
				std::vector {
					VertexAttributes{ 0, Space::Point3D::Size(), GL_FLOAT, GL_FALSE, sizeof(Vertex), 0 }, // Position
					VertexAttributes{ 1, Space::Color::Size(), GL_FLOAT, GL_FALSE, sizeof(Vertex), sizeof(Space::Point3D)}, // Color
					VertexAttributes{ 2, Math::Vec3::Size(), GL_FLOAT, GL_FALSE, sizeof(Vertex), sizeof(Space::Point3D) + sizeof(Space::Color)} // Normal
				} 
			)
		{
			ConstructCube(halfExtent, color);
			Init();
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

			std::vector<CubeFace> faces = {
				{{0, 0, -1}, {{ {-h, -h, -h}, { h, -h, -h}, { h,  h, -h}, {-h,  h, -h} }}},	// back face (-Z)
				{{0, 0, 1},  {{ {-h, -h,  h}, { h, -h,  h}, { h,  h,  h}, {-h,  h,  h} }}},	// front face (+Z)
				{{-1, 0, 0}, {{ {-h, -h,  h}, {-h, -h, -h}, {-h,  h, -h}, {-h,  h,  h} }}}, // left face (-X)
				{{1, 0, 0},  {{ { h, -h, -h}, { h, -h,  h}, { h,  h,  h}, { h,  h, -h} }}}, // right face (+X)
				{{0, -1, 0}, {{ {-h, -h,  h}, { h, -h,  h}, { h, -h, -h}, {-h, -h, -h} }}}, // bottom face (-Y)
				{{0, 1, 0},  {{ {-h,  h, -h}, { h,  h, -h}, { h,  h,  h}, {-h,  h,  h} }}}	// top face (+Y)
			};

			unsigned int indexOffset = 0;
			for (const auto& face : faces)
			{
				for (const auto& pos : face.vertices)
				{
					m_vertices.emplace_back(Space::Point3D(pos.x, pos.y, pos.z), color, MathUtils::FromGLM(face.normal));
				}

				// Add indices for two triangles (0,1,2) and (2,3,0) of this face
				m_indices.push_back(indexOffset + 0);
				m_indices.push_back(indexOffset + 1);
				m_indices.push_back(indexOffset + 2);
				m_indices.push_back(indexOffset + 2);
				m_indices.push_back(indexOffset + 3);
				m_indices.push_back(indexOffset + 0);

				indexOffset += 4;
			}
		}
	}
}
