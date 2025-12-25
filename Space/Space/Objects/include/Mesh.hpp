#ifndef ANDROMEDA__SPACE__MESH__HPP
#define ANDROMEDA__SPACE__MESH__HPP


#include "../../MacroExports/include/MacroExports.hpp"
#include "pch.hpp"
#include "Andromeda/Space/Vertices/Vertex.hpp"
#include "Andromeda/Space/Objects/IMesh.hpp"


namespace Andromeda::Space
{
	class SPACE_API Mesh
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
		// Setters
		void SetData(
			const std::vector<Vertex>& vertices,
			const std::vector<unsigned int>& indices
		);

	protected:
		std::vector<unsigned int> m_indices;
		std::vector<Vertex> m_vertices;
	};
}


#endif // ANDROMEDA__SPACE__MESH__HPP