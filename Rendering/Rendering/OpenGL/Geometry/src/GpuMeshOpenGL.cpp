#include "../include/GpuMeshOpenGL.hpp"
#include "../../Vertices/include/VertexLayoutOpenGL.hpp"
#include "glad/gl.h"


namespace Andromeda::Rendering
{
    GpuMeshOpenGL::GpuMeshOpenGL()
        : m_VAO{ 0 }
        , m_VBO{ 0 }
        , m_EBO{ 0 }
        , m_IndexCount{ 0 }
    {
    }

    GpuMeshOpenGL::~GpuMeshOpenGL()
    {
        Destroy();
    }

    GpuMeshOpenGL::GpuMeshOpenGL(GpuMeshOpenGL&& other) noexcept
        : m_VAO{ 0 }
        , m_VBO{ 0 }
        , m_EBO{ 0 }
        , m_IndexCount{ 0 }
    {
        MoveFrom(other);
    }

    GpuMeshOpenGL& GpuMeshOpenGL::operator=(GpuMeshOpenGL&& other) noexcept
    {
        if (this != &other)
        {
            Destroy();
            MoveFrom(other);
        }
        return *this;
    }

    void GpuMeshOpenGL::MoveFrom(GpuMeshOpenGL& other) noexcept
    {
        m_VAO = other.m_VAO;
        m_VBO = other.m_VBO;
        m_EBO = other.m_EBO;
        m_IndexCount = other.m_IndexCount;

        other.m_VAO = 0;
        other.m_VBO = 0;
        other.m_EBO = 0;
        other.m_IndexCount = 0;
    }

    bool GpuMeshOpenGL::IsValid() const
    {
        return m_VAO != 0;
    }

    void GpuMeshOpenGL::Create(
        const void* vertexData,
        size_t vertexDataSizeBytes,
        const std::vector<uint32_t>& indices,
        const Andromeda::Rendering::VertexLayout& layout
    )
    {
        Destroy();

        m_IndexCount = static_cast<uint32_t>(indices.size());

        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
        glGenBuffers(1, &m_EBO);

        glBindVertexArray(m_VAO);

        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(vertexDataSizeBytes), vertexData, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(indices.size() * sizeof(uint32_t)), indices.data(), GL_STATIC_DRAW);

        VertexLayoutOpenGL::Apply(layout);

        glBindVertexArray(0);
    }

    void GpuMeshOpenGL::Destroy()
    {
        if (m_EBO != 0)
        {
            glDeleteBuffers(1, &m_EBO);
            m_EBO = 0;
        }
        if (m_VBO != 0)
        {
            glDeleteBuffers(1, &m_VBO);
            m_VBO = 0;
        }
        if (m_VAO != 0)
        {
            glDeleteVertexArrays(1, &m_VAO);
            m_VAO = 0;
        }

        m_IndexCount = 0;
    }

    uint32_t GpuMeshOpenGL::GetVAO() const
    {
        return m_VAO;
    }

    uint32_t GpuMeshOpenGL::GetVBO() const
    {
        return m_VBO;
    }

    uint32_t GpuMeshOpenGL::GetEBO() const
    {
        return m_EBO;
    }

    uint32_t GpuMeshOpenGL::GetIndexCount() const
    {
        return m_IndexCount;
    }
}
