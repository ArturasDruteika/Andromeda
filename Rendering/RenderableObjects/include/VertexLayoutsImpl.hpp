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