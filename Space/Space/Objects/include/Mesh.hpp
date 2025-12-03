#ifndef RENDERING__ABSTRACTS__MESH__HPP
#define RENDERING__ABSTRACTS__MESH__HPP


#include "pch.hpp"
#include "Space/Vertices/include/Vertex.hpp"


namespace Andromeda::Space
{
	class Mesh
	{
	public:
		Mesh();
		~Mesh();

		// Getters
		unsigned int GetIndexCount() const;
		unsigned int GetVertexCount() const;
		const std::vector<unsigned int>& GetIndices() const;
		const std::vector<Space::Vertex>& GetVertices() const;

	protected:
		std::vector<unsigned int> m_indices;
		std::vector<Space::Vertex> m_vertices;
	};
}


#endif // RENDERING__ABSTRACTS__MESH__HPP