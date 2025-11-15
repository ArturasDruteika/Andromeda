#include "../include/CubeObjectOpenGLImpl.hpp"
#include "../../../Utils/include/MathUtils.hpp"
#include "Constants.hpp"
#include "Points.hpp"
#include "glad/gl.h"


namespace Andromeda::Rendering
{
	struct CubeFace
	{
		glm::vec3 normal;
		std::array<glm::vec3, 4> vertices;
	};


	CubeObjectOpenGL::CubeObjectOpenGLImpl::CubeObjectOpenGLImpl(const Math::Vec3& centerPosition, float halfExtent, const PhysicalProperties::Color& color)
		: m_halfExtent{ halfExtent }
		, RenderableObjectOpenGL(
			centerPosition,
			color,
			std::vector {
				VertexAttributes{ 0, PhysicalProperties::Point3D::Size(), GL_FLOAT, GL_FALSE, sizeof(PhysicalProperties::Vertex), 0 }, // Position
				VertexAttributes{ 1, PhysicalProperties::Color::Size(), GL_FLOAT, GL_FALSE, sizeof(PhysicalProperties::Vertex), sizeof(PhysicalProperties::Point3D)}, // Color
				VertexAttributes{ 2, Math::Vec3::Size(), GL_FLOAT, GL_FALSE, sizeof(PhysicalProperties::Vertex), sizeof(PhysicalProperties::Point3D) + sizeof(PhysicalProperties::Color)} // Normal
			} 
		)
	{
		ConstructCube(halfExtent, color);
		Init();
		UpdateModelMatrix(PhysicalProperties::TransformationType::ALL);
	}

	CubeObjectOpenGL::CubeObjectOpenGLImpl::~CubeObjectOpenGLImpl() = default;

	float CubeObjectOpenGL::CubeObjectOpenGLImpl::GetHalfExtent() const
	{
		return m_halfExtent;
	}

	void CubeObjectOpenGL::CubeObjectOpenGLImpl::SetHalfExtent(float halfExtent)
	{
	}

	void CubeObjectOpenGL::CubeObjectOpenGLImpl::ConstructCube(float halfExtent, const PhysicalProperties::Color& color)
	{
		const float h = halfExtent;

		std::vector<CubeFace> faces = {
			{{0, 0, -1}, {{ {-h, -h, -h}, {-h,  h, -h}, { h,  h, -h}, { h, -h, -h} }}}, // Back face (-Z)
			{{0, 0, 1},  {{ {-h, -h,  h}, { h, -h,  h}, { h,  h,  h}, {-h,  h,  h} }}}, // Front face (+Z)
			{{-1, 0, 0}, {{ {-h, -h, -h}, {-h, -h,  h}, {-h,  h,  h}, {-h,  h, -h} }}}, // Left face (-X)
			{{1, 0, 0},  {{ { h, -h, -h}, { h,  h, -h}, { h,  h,  h}, { h, -h,  h} }}}, // Right face (+X)
			{{0, -1, 0}, {{ {-h, -h, -h}, { h, -h, -h}, { h, -h,  h}, {-h, -h,  h} }}}, // Bottom face (-Y)
			{{0, 1, 0},  {{ {-h,  h,  h}, { h,  h,  h}, { h,  h, -h}, {-h,  h, -h} }}}  // Top face (+Y)
		};

		unsigned int indexOffset = 0;
		for (const auto& face : faces)
		{
			for (const auto& pos : face.vertices)
			{
				m_vertices.emplace_back(PhysicalProperties::Point3D(pos.x, pos.y, pos.z), color, MathUtils::FromGLM(face.normal));
			}

			// Triangle 1: 0, 1, 2 - Triangle 2: 2, 3, 0
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
