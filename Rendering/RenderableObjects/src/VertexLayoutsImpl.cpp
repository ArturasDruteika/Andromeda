#include "../include/VertexLayoutsImpl.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		VertexLayout::VertexLayoutImpl::VertexLayoutImpl(const std::vector<VertexAttributes>& vertexAttributes)
			: m_verticesAttributesVec{ vertexAttributes }
			, m_stride{ 0 }
		{
			CalculateStride(vertexAttributes);
		}

		VertexLayout::VertexLayoutImpl::~VertexLayoutImpl() = default;

		VertexLayout::VertexLayoutImpl::VertexLayoutImpl(const VertexLayoutImpl& other)
			: m_verticesAttributesVec(other.m_verticesAttributesVec), m_stride(other.m_stride)
		{
		}

		const std::vector<VertexAttributes>& VertexLayout::VertexLayoutImpl::GetVerticesAttributesVec() const
		{
			return m_verticesAttributesVec;
		}

		size_t VertexLayout::VertexLayoutImpl::GetStride() const
		{
			return m_stride;
		}

		void VertexLayout::VertexLayoutImpl::CalculateStride(const std::vector<VertexAttributes>& vertexAttributes)
		{
			for (const VertexAttributes& attr : vertexAttributes)
			{
				m_stride += attr.size * sizeof(float); // Assuming float-based attributes
			}
		}
	}
}
