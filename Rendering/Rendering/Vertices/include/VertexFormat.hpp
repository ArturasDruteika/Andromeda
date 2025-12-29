#ifndef RENDERING__VERTICES__VERTEX_FORMAT__HPP
#define RENDERING__VERTICES__VERTEX_FORMAT__HPP


#include "pch.hpp"


namespace Andromeda::Rendering
{
    enum class VertexSemantic
    {
        Position,
        Color0,
        Normal,
        Tangent,
        Bitangent,
        TexCoord0,
        TexCoord1,
        Joints0,
        Weights0
    };

    enum class ComponentType
    {
        Float32,
        Int32,
        UInt32,
        UInt16,
        UInt8
    };

    size_t ComponentTypeSizeBytes(ComponentType type);
    bool IsIntegerComponentType(ComponentType type);
}


#endif // RENDERING__VERTICES__VERTEX_FORMAT__HPP