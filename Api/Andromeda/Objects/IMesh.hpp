#ifndef API__RENDERABLE_OBJECTS__I_MESH__HPP
#define API__RENDERABLE_OBJECTS__I_MESH__HPP


#include "Space/Vertices/include/Vertex.hpp"
#include <vector>


namespace Andromeda
{
	class IMesh
	{
	public:
		virtual ~IMesh() = default;
		
		virtual unsigned int GetIndexCount() const = 0;
		virtual unsigned int GetVertexCount() const = 0;
		virtual const std::vector<unsigned int>& GetIndices() const = 0;
		virtual const std::vector<Space::Vertex>& GetVertices() const = 0;
	};
}


#endif // API__RENDERABLE_OBJECTS__I_MESH__HPP