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
			m_pVertexLayoutImpl = nullptr;
		}

		VertexLayout::VertexLayout(const VertexLayout& other)
		{
			m_pVertexLayoutImpl = new VertexLayoutImpl(*other.m_pVertexLayoutImpl);
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
