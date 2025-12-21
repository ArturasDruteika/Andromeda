#ifndef RENDERING__VERTICES__VERTEX_LOCATION_POLICY__HPP
#define RENDERING__VERTICES__VERTEX_LOCATION_POLICY__HPP

#include "VertexFormat.hpp"
#include "pch.hpp"


namespace Andromeda::Rendering
{
    class VertexLocationPolicy
    {
    public:
        static uint32_t GetLocation(VertexSemantic semantic);
    };
}

#endif // RENDERING__VERTICES__VERTEX_LOCATION_POLICY__HPP
