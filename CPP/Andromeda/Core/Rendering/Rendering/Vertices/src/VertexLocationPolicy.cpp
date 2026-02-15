#include "../include/VertexLocationPolicy.hpp"

namespace Andromeda::Rendering
{
    uint32_t VertexLocationPolicy::GetLocation(VertexSemantic semantic)
    {
        switch (semantic)
        {
        case VertexSemantic::Position:  return 0;
        case VertexSemantic::Color0:    return 1;
        case VertexSemantic::Normal:    return 2;
        //case VertexSemantic::Tangent:   return 3;
        //case VertexSemantic::Bitangent: return 4;
        //case VertexSemantic::TexCoord0: return 5;
        //case VertexSemantic::TexCoord1: return 6;
        //case VertexSemantic::Joints0:   return 7;
        //case VertexSemantic::Weights0:  return 8;
        default:                        return 0;
        }
    }
}
