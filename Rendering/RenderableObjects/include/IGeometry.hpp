#ifndef RENDERING__I_GEOMETRY__HPP
#define RENDERING__I_GEOMETRY__HPP


#if defined(_WIN32)
	#if defined(RENDERING_EXPORT)
		#define RENDERING_API __declspec(dllexport)
	#else
		#define RENDERING_API __declspec(dllimport)
	#endif /* RENDERING_API */
	#define _sprintf sprintf_s
#endif

#if defined(__GNUC__)
	// GCC
	#define RENDERING_API __attribute__((visibility("default")))
#endif


#include "pch.hpp"
#include "../../Vertices/include/Vertex.hpp"


namespace Andromeda::Rendering
{
	class RENDERING_API IGeometry
	{
	public:
		virtual ~IGeometry();

		// Getters
		virtual unsigned int GetVertexCount() const = 0;
		virtual unsigned int GetIndicesCount() const = 0;
		virtual std::vector<Vertex> GetVertices() const = 0;
	};
}


#endif // RENDERING__I_GEOMETRY__HPP