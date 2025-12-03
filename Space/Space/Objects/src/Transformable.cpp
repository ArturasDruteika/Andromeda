#include "../include/Mesh.hpp"


namespace Andromeda::Space
{
	Mesh::Mesh() = default;

	Mesh::~Mesh() = default;

	unsigned int Mesh::GetIndexCount() const
	{
		return m_indices.size();
	}

	unsigned int Mesh::GetVertexCount() const
	{
		return m_vertices.size();
	}

	const std::vector<unsigned int>& Mesh::GetIndices() const
	{
		return m_indices;
	}

	const std::vector<Space::Vertex>& Mesh::GetVertices() const
	{
		return m_vertices;
	}
}
