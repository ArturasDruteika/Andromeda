#include "../include/Geometry.hpp"


namespace Andromeda::Rendering
{
	Geometry::Geometry()
	{
	}

	Geometry::~Geometry() = default;

	unsigned int Geometry::GetIndicesCount() const
	{
		return m_indicesCount;
	}

	unsigned int Geometry::GetVerticesCount() const
	{
		return m_vertexCount;
	}

	std::vector<unsigned int> Geometry::GetIndices() const
	{
		return m_indices;
	}

	std::vector<Vertex> Geometry::GetVertices() const
	{
		return m_vertices;
	}
}
