#ifndef ANDROMEDA__SPACE__MESH__HPP
#define ANDROMEDA__SPACE__MESH__HPP


#include "pch.hpp"
#include "Andromeda/Space/Vertices/Vertex.hpp"
#include "Andromeda/Space/Objects/IMesh.hpp"


namespace Andromeda::Space
{
	class Mesh
		: public virtual IMesh
	{
	public:
		Mesh();
		~Mesh();

		// Getters
		unsigned int GetIndexCount() const override;
		unsigned int GetVertexCount() const override;
		const std::vector<unsigned int>& GetIndices() const override;
		const std::vector<Vertex>& GetVertices() const override;

	protected:
		std::vector<unsigned int> m_indices;
		std::vector<Vertex> m_vertices;
	};
}


#endif // ANDROMEDA__SPACE__MESH__HPP