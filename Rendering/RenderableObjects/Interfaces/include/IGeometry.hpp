#ifndef RENDERING__INTERFACES__I_GEOMETRY__HPP
#define RENDERING__INTERFACES__I_GEOMETRY__HPP


#include "../../../MacroExports/include/MacroExports.hpp"
#include "pch.hpp"
#include "../../../Vertices/include/Vertex.hpp"


namespace Andromeda::Rendering
{
	class RENDERING_API IGeometry
	{
	public:
		virtual ~IGeometry();

		// Getters
		virtual unsigned int GetIndicesCount() const = 0;
		virtual unsigned int GetVerticesCount() const = 0;
		virtual std::vector<unsigned int> GetIndices() const = 0;
		virtual std::vector<Vertex> GetVertices() const = 0;
	};
}


#endif // RENDERING__INTERFACES__I_GEOMETRY__HPP