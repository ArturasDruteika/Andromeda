#include "../include/VertexLayoutOpenGL.hpp"
#include "../../../Vertices/include/VertexFormat.hpp"
#include "../../../Vertices/include/VertexLocationPolicy.hpp"

#include "glad/gl.h"


namespace Andromeda::Rendering
{
    static GLenum ToGLComponentType(Andromeda::Rendering::ComponentType type)
    {
        switch (type)
        {
            case Andromeda::Rendering::ComponentType::Float32: return GL_FLOAT;
            case Andromeda::Rendering::ComponentType::Int32:   return GL_INT;
            case Andromeda::Rendering::ComponentType::UInt32:  return GL_UNSIGNED_INT;
            case Andromeda::Rendering::ComponentType::UInt16:  return GL_UNSIGNED_SHORT;
            case Andromeda::Rendering::ComponentType::UInt8:   return GL_UNSIGNED_BYTE;
            default:                                           return GL_FLOAT;
        }
    }

    static bool IsIntegerType(Andromeda::Rendering::ComponentType type)
    {
        return Andromeda::Rendering::IsIntegerComponentType(type);
    }

    void VertexLayoutOpenGL::Apply(const Andromeda::Rendering::VertexLayout& layout)
    {
        const std::vector<VertexAttributeDesc>& attrs = layout.GetAttributes();
        const GLsizei stride = static_cast<GLsizei>(layout.GetStrideBytes());

        for (const VertexAttributeDesc& attr : attrs)
        {
            const GLuint location = static_cast<GLuint>(Andromeda::Rendering::VertexLocationPolicy::GetLocation(attr.semantic));
            const void* offsetPtr = reinterpret_cast<const void*>(attr.offsetBytes);

            glEnableVertexAttribArray(location);

            if (IsIntegerType(attr.componentType))
            {
                glVertexAttribIPointer(
                    location,
                    static_cast<GLint>(attr.componentCount),
                    ToGLComponentType(attr.componentType),
                    stride,
                    offsetPtr
                );
            }
            else
            {
                glVertexAttribPointer(
                    location,
                    static_cast<GLint>(attr.componentCount),
                    ToGLComponentType(attr.componentType),
                    attr.normalized ? GL_TRUE : GL_FALSE,
                    stride,
                    offsetPtr
                );
            }

            if (layout.GetInputRate() == Andromeda::Rendering::InputRate::PerInstance)
            {
                glVertexAttribDivisor(location, 1);
            }
        }
    }
}
