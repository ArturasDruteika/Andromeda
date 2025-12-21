#ifndef RENDERING__VERTICES__VERTEX_LAYOUT_OPENGL__HPP
#define RENDERING__VERTICES__VERTEX_LAYOUT_OPENGL__HPP


#include "../../../Vertices/include/VertexLayouts.hpp"


namespace Andromeda::Rendering
{
    class VertexLayoutOpenGL
    {
    public:
        static void Apply(const Andromeda::Rendering::VertexLayout& layout);
    };
}

#endif // RENDERING__VERTICES__VERTEX_LAYOUT_OPENGL__HPP
