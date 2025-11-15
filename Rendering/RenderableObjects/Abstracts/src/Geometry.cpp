#include "../include/Geometry.hpp"


namespace Andromeda::Rendering
{
	Geometry::Geometry() = default;

	Geometry::~Geometry() = default;

	unsigned int Geometry::GetIndicesCount() const
	{
		return m_indices.size();
	}

	unsigned int Geometry::GetVerticesCount() const
	{
		return m_vertices.size();
	}

	std::vector<unsigned int> Geometry::GetIndices() const
	{
		return m_indices;
	}

	std::vector<PhysicalProperties::Vertex> Geometry::GetVertices() const
	{
		return m_vertices;
	}
}
