#ifndef RENDERING__VERTEX_LAYOUTS_IMPL__HPP
#define RENDERING__VERTEX_LAYOUTS_IMPL__HPP


#include "../include/VertexLayouts.hpp"
#include "../include/VertexAttributes.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		class VertexLayout::VertexLayoutImpl
		{
		public:
			VertexLayoutImpl(const std::vector<VertexAttributes>& vertexAttributes);
			~VertexLayoutImpl();

			VertexLayoutImpl(const VertexLayoutImpl& other);
			VertexLayoutImpl& operator=(const VertexLayoutImpl& other) = delete;	// Prevent Copy Assignment
			VertexLayoutImpl(VertexLayoutImpl&& other) noexcept = delete;	// Prevent Move Constructor
			VertexLayoutImpl& operator=(VertexLayoutImpl&& other) noexcept = delete;	// Prevent Move Assignment

			const std::vector<VertexAttributes>& GetVerticesAttributesVec() const;
			size_t GetStride() const;

		private:
			void CalculateStride(const std::vector<VertexAttributes>& vertexAttributes);

			std::vector<VertexAttributes> m_verticesAttributesVec;
			size_t m_stride;
		};

	}
}


#endif // RENDERING__VERTEX_LAYOUTS_IMPL__HPP