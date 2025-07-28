#ifndef RENDERING__ABSTRACTS__GEOMETRY__HPP
#define RENDERING__ABSTRACTS__GEOMETRY__HPP


#include "pch.hpp"
#include "../../../Vertices/include/Vertex.hpp"


namespace Andromeda::Rendering
{
	class Geometry
	{
	public:
		Geometry();
		~Geometry();

		// Getters
		unsigned int GetIndicesCount() const;
		unsigned int GetVerticesCount() const;
		std::vector<unsigned int> GetIndices() const;
		std::vector<Vertex> GetVertices() const;

	protected:
		unsigned int m_vertexCount;
		unsigned int m_indicesCount;
		std::vector<unsigned int> m_indices;
		std::vector<Vertex> m_vertices;
	};
}


#endif // RENDERING__ABSTRACTS__GEOMETRY__HPP