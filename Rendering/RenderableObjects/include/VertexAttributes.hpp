#ifndef RENDERING__VERTEX_ATTRIBUTES__HPP
#define RENDERING__VERTEX_ATTRIBUTES__HPP


namespace Andromeda
{
	namespace Rendering
	{
        struct VertexAttributes
        {
            unsigned int index = 0;  // Location in shader
            int size = -1;            // Number of components (e.g., 3 for vec3)
            unsigned int type = 0;   // GL_FLOAT, GL_INT, etc.
            bool normalized = false;     // Should it be normalized?
            size_t stride = 0;       // Offset between attributes
            size_t offset = 0;       // Byte offset in struct
        };
	}
}


#endif // RENDERING__VERTEX_ATTRIBUTES__HPP