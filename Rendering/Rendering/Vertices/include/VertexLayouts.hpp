#ifndef RENDERING__VERTICES__VERTEX_LAYOUTS__HPP
#define RENDERING__VERTICES__VERTEX_LAYOUTS__HPP

#include "VertexFormat.hpp"
#include "pch.hpp"

namespace Andromeda::Rendering
{
    enum class InputRate
    {
        PerVertex,
        PerInstance
    };

    struct VertexAttributeDesc
    {
        VertexSemantic semantic = VertexSemantic::Position;
        ComponentType componentType = ComponentType::Float32;
        uint32_t componentCount = 0;
        bool normalized = false;

        size_t offsetBytes = 0;
    };

    class VertexLayout
    {
    public:
        VertexLayout();
        explicit VertexLayout(const std::vector<VertexAttributeDesc>& attributes, InputRate inputRate = InputRate::PerVertex);

        const std::vector<VertexAttributeDesc>& GetAttributes() const;
        size_t GetStrideBytes() const;
        InputRate GetInputRate() const;

    private:
        void CalculateOffsetsAndStride();

    private:
        std::vector<VertexAttributeDesc> m_attributes;
        size_t m_strideBytes;
        InputRate m_inputRate;
    };
}

#endif // RENDERING__VERTICES__VERTEX_LAYOUTS__HPP
