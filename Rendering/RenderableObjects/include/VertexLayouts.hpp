#ifndef RENDERING__VERTEX_LAYOUTS__HPP
#define RENDERING__VERTEX_LAYOUTS__HPP


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
#include "../include/VertexAttributes.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		class RENDERING_API VertexLayout
		{
		public:
			VertexLayout(const std::vector<VertexAttributes>& vertexAttributes);
			~VertexLayout();

			VertexLayout(const VertexLayout& other);	// Prevent Copy Constructor
			VertexLayout& operator=(const VertexLayout& other) = delete;	// Prevent Copy Assignment
			VertexLayout(VertexLayout&& other) noexcept = delete;	// Prevent Move Constructor
			VertexLayout& operator=(VertexLayout&& other) noexcept = delete;	// Prevent Move Assignment

			const std::vector<VertexAttributes>& GetVerticesAttributesVec() const;
			size_t GetStride() const;

		private:
			class VertexLayoutImpl;
			VertexLayoutImpl* m_pVertexLayoutImpl;
		};
	}
}


#endif // RENDERING__VERTEX_LAYOUTS__HPP