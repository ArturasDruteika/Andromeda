#ifndef RENDERING__VERTEX_LAYOUTS_IMPL__HPP
#define RENDERING__VERTEX_LAYOUTS_IMPL__HPP


#include "../include/VertexAttributes.hpp"


namespace Andromeda::Rendering
{
	class VertexLayout
	{
	public:
		VertexLayout(const std::vector<VertexAttributes>& vertexAttributes);
		~VertexLayout();

		VertexLayout(const VertexLayout& other);
		VertexLayout& operator=(const VertexLayout& other) = delete;	// Prevent Copy Assignment
		VertexLayout(VertexLayout&& other) noexcept = delete;	// Prevent Move Constructor
		VertexLayout& operator=(VertexLayout&& other) noexcept = delete;	// Prevent Move Assignment

		const std::vector<VertexAttributes>& GetVerticesAttributesVec() const;
		size_t GetStride() const;

	private:
		void CalculateStride(const std::vector<VertexAttributes>& vertexAttributes);

		std::vector<VertexAttributes> m_verticesAttributesVec;
		size_t m_stride;
	};
}


#endif // RENDERING__VERTEX_LAYOUTS_IMPL__HPP