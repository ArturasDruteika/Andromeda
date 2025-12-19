#include "../include/Cube.hpp"
#include "spdlog/spdlog.h"


namespace Andromeda::Space
{
	Cube::Cube(float halfExtent, const Math::Vec3& position, const Color& color)
		: GeometricObject(position, color)
		, m_halfExtent(halfExtent)
	{
		ConstructCube(m_halfExtent, color);
	}

	Cube::~Cube() = default;

	float Cube::GetHalfExtent() const
	{
		return m_halfExtent;
	}

	void Cube::SetHalfExtent(float halfExtent)
	{
		if (halfExtent <= 0.0f)
		{
			spdlog::error("Cube half-extent must be greater than zero. Given half-extent: {}", halfExtent);
			return;
		}

		m_halfExtent = halfExtent;
		ConstructCube(m_halfExtent, m_color);
	}

	void Cube::ConstructCube(float halfExtent, const Color& color)
	{
		if (halfExtent <= 0.0f)
		{
			spdlog::error("Cube half-extent must be greater than zero. Given half-extent: {}", halfExtent);
			return;
		}

		const float h = halfExtent;

		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		ReserveCubeBuffers(vertices, indices);

		const auto faces = BuildCubeFaces(h);

		unsigned int indexOffset = 0;
		for (const auto& face : faces)
		{
			AppendFace(face, color, vertices, indices, indexOffset);
		}

		Mesh mesh;
		mesh.SetData(vertices, indices);

		SetMesh(mesh);
	}

	std::array<CubeFaceData, 6> Cube::BuildCubeFaces(float halfExtent)
	{
		return std::array<CubeFaceData, 6>
		{
			CubeFaceData
			{
				Math::Vec3(0.0f, 0.0f, -1.0f),
				{
					Math::Vec3(-halfExtent, -halfExtent, -halfExtent),
					Math::Vec3(-halfExtent,  halfExtent, -halfExtent),
					Math::Vec3(halfExtent,  halfExtent, -halfExtent),
					Math::Vec3(halfExtent, -halfExtent, -halfExtent)
				}
			}, // Back (-Z)

				CubeFaceData
			{
				Math::Vec3(0.0f, 0.0f,  1.0f),
				{
					Math::Vec3(-halfExtent, -halfExtent,  halfExtent),
					Math::Vec3(halfExtent, -halfExtent,  halfExtent),
					Math::Vec3(halfExtent,  halfExtent,  halfExtent),
					Math::Vec3(-halfExtent,  halfExtent,  halfExtent)
				}
			}, // Front (+Z)

				CubeFaceData
			{
				Math::Vec3(-1.0f, 0.0f, 0.0f),
				{
					Math::Vec3(-halfExtent, -halfExtent, -halfExtent),
					Math::Vec3(-halfExtent, -halfExtent,  halfExtent),
					Math::Vec3(-halfExtent,  halfExtent,  halfExtent),
					Math::Vec3(-halfExtent,  halfExtent, -halfExtent)
				}
			}, // Left (-X)

				CubeFaceData
			{
				Math::Vec3(1.0f, 0.0f, 0.0f),
				{
					Math::Vec3(halfExtent, -halfExtent, -halfExtent),
					Math::Vec3(halfExtent,  halfExtent, -halfExtent),
					Math::Vec3(halfExtent,  halfExtent,  halfExtent),
					Math::Vec3(halfExtent, -halfExtent,  halfExtent)
				}
			}, // Right (+X)

				CubeFaceData
			{
				Math::Vec3(0.0f, -1.0f, 0.0f),
				{
					Math::Vec3(-halfExtent, -halfExtent, -halfExtent),
					Math::Vec3(halfExtent, -halfExtent, -halfExtent),
					Math::Vec3(halfExtent, -halfExtent,  halfExtent),
					Math::Vec3(-halfExtent, -halfExtent,  halfExtent)
				}
			}, // Bottom (-Y)

				CubeFaceData
			{
				Math::Vec3(0.0f,  1.0f, 0.0f),
				{
					Math::Vec3(-halfExtent,  halfExtent,  halfExtent),
					Math::Vec3(halfExtent,  halfExtent,  halfExtent),
					Math::Vec3(halfExtent,  halfExtent, -halfExtent),
					Math::Vec3(-halfExtent,  halfExtent, -halfExtent)
				}
			}  // Top (+Y)
		};
	}

	void Cube::ReserveCubeBuffers(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
	{
		// 6 faces * 4 verts each = 24 verts (flat normals per face)
		// 6 faces * 2 triangles each * 3 = 36 indices
		vertices.reserve(24);
		indices.reserve(36);
	}

	void Cube::AppendFace(
		const CubeFaceData& face, 
		const Color& color, 
		std::vector<Vertex>& outVertices, 
		std::vector<unsigned int>& outIndices, 
		unsigned int& indexOffset
	)
	{
		for (const auto& pos : face.vertices)
		{
			outVertices.emplace_back(
				pos,
				color,
				face.normal
			);
		}

		// Two triangles: (0,1,2) and (2,3,0) in face-local quad
		outIndices.push_back(indexOffset + 0);
		outIndices.push_back(indexOffset + 1);
		outIndices.push_back(indexOffset + 2);

		outIndices.push_back(indexOffset + 2);
		outIndices.push_back(indexOffset + 3);
		outIndices.push_back(indexOffset + 0);

		indexOffset += 4;
	}
}

