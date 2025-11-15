#ifndef RENDERING__ABSTRACTS__GEOMETRY__HPP
#define RENDERING__ABSTRACTS__GEOMETRY__HPP


#include "pch.hpp"
#include "Vertex.hpp"


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
		std::vector<PhysicalProperties::Vertex> GetVertices() const;

	protected:
		std::vector<unsigned int> m_indices;
		std::vector<PhysicalProperties::Vertex> m_vertices;
	};
}


#endif // RENDERING__ABSTRACTS__GEOMETRY__HPP