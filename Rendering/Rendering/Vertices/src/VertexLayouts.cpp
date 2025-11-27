#include "../include/VertexLayouts.hpp"


namespace Andromeda::Rendering
{
	VertexLayout::VertexLayout(const std::vector<VertexAttributes>& vertexAttributes)
		: m_verticesAttributesVec{ vertexAttributes }
		, m_stride{ 0 }
	{
		CalculateStride(vertexAttributes);
	}

	VertexLayout::~VertexLayout() = default;

	VertexLayout::VertexLayout(const VertexLayout& other)
		: m_verticesAttributesVec(other.m_verticesAttributesVec), m_stride(other.m_stride)
	{
	}

	const std::vector<VertexAttributes>& VertexLayout::GetVerticesAttributesVec() const
	{
		return m_verticesAttributesVec;
	}

	size_t VertexLayout::GetStride() const
	{
		return m_stride;
	}

	void VertexLayout::CalculateStride(const std::vector<VertexAttributes>& vertexAttributes)
	{
		for (const VertexAttributes& attr : vertexAttributes)
		{
			m_stride += attr.size * sizeof(float); // Assuming float-based attributes
		}
	}
}
