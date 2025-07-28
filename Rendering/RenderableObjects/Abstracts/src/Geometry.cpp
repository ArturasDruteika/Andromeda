#include "../include/Geometry.hpp"


namespace Andromeda::Rendering
{
	Geometry::Geometry()
	{
	}

	Geometry::~Geometry() = default;

	unsigned int Geometry::GetVertexCount() const
	{
		return m_vertexCount;
	}

	unsigned int Geometry::GetIndicesCount() const
	{
		return m_indicesCount;
	}

	const std::vector<unsigned int> Geometry::GetIndices() const
	{
		return m_indices;
	}

	std::vector<Vertex> Geometry::GetVertices() const
	{
		return m_vertices;
	}
}
