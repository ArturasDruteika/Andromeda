#include "../include/VertexLayouts.hpp"


namespace Andromeda::Rendering
{
    VertexLayout::VertexLayout()
        : m_attributes{}
        , m_strideBytes{ 0 }
        , m_inputRate{ InputRate::PerVertex }
    {
    }

    VertexLayout::VertexLayout(const std::vector<VertexAttributeDesc>& attributes, InputRate inputRate)
        : m_attributes(attributes)
        , m_strideBytes(0)
        , m_inputRate(inputRate)
    {
        CalculateOffsetsAndStride();
    }

    const std::vector<VertexAttributeDesc>& VertexLayout::GetAttributes() const
    {
        return m_attributes;
    }

    size_t VertexLayout::GetStrideBytes() const
    {
        return m_strideBytes;
    }

    InputRate VertexLayout::GetInputRate() const
    {
        return m_inputRate;
    }

    void VertexLayout::CalculateOffsetsAndStride()
    {
        size_t offset = 0;

        for (auto& attr : m_attributes)
        {
            attr.offsetBytes = offset;
            offset += static_cast<size_t>(attr.componentCount) * ComponentTypeSizeBytes(attr.componentType);
        }

        m_strideBytes = offset;
    }
}
