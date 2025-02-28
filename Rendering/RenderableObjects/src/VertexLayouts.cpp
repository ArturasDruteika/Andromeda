#include "../include/VertexLayouts.hpp"
#include "../include/VertexLayoutsImpl.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		VertexLayout::VertexLayout(const std::vector<VertexAttributes>& vertexAttributes)
			: m_pVertexLayoutImpl{ new VertexLayout::VertexLayoutImpl{ vertexAttributes } }
		{
		}

		VertexLayout::~VertexLayout()
		{
			delete m_pVertexLayoutImpl;
		}

		const std::vector<VertexAttributes>& VertexLayout::GetVerticesAttributesVec() const
		{
			return m_pVertexLayoutImpl->GetVerticesAttributesVec();
		}

		size_t VertexLayout::GetStride() const
		{
			return m_pVertexLayoutImpl->GetStride();
		}
	}
}
