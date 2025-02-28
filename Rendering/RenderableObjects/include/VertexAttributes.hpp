#ifndef RENDERING__VERTEX_ATTRIBUTES__HPP
#define RENDERING__VERTEX_ATTRIBUTES__HPP


namespace Andromeda
{
	namespace Rendering
	{
        struct VertexAttributes
        {
            unsigned int index;  // Location in shader
            int size;            // Number of components (e.g., 3 for vec3)
            unsigned int type;   // GL_FLOAT, GL_INT, etc.
            bool normalized;     // Should it be normalized?
            size_t stride;       // Offset between attributes
            size_t offset;       // Byte offset in struct
        };
	}
}


#endif // RENDERING__VERTEX_ATTRIBUTES__HPP