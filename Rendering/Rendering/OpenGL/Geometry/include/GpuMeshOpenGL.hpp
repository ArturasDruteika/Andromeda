#ifndef RENDERING__GEOMETRY__GPU_MESH_OPENGL__HPP
#define RENDERING__GEOMETRY__GPU_MESH_OPENGL__HPP


#include "../../../Vertices/include/VertexLayouts.hpp"
#include "pch.hpp"


namespace Andromeda::Rendering
{
    class GpuMeshOpenGL
    {
    public:
        GpuMeshOpenGL();
        ~GpuMeshOpenGL();

        GpuMeshOpenGL(const GpuMeshOpenGL& other) = delete;
        GpuMeshOpenGL& operator=(const GpuMeshOpenGL& other) = delete;

        GpuMeshOpenGL(GpuMeshOpenGL&& other) noexcept;
        GpuMeshOpenGL& operator=(GpuMeshOpenGL&& other) noexcept;

        bool IsValid() const;

        void Create(
            const void* vertexData,
            size_t vertexDataSizeBytes,
            const std::vector<uint32_t>& indices,
            const Andromeda::Rendering::VertexLayout& layout
        );

        void Destroy();

        uint32_t GetVAO() const;
        uint32_t GetVBO() const;
        uint32_t GetEBO() const;
        uint32_t GetIndexCount() const;

    private:
        void MoveFrom(GpuMeshOpenGL& other) noexcept;

    private:
        uint32_t m_VAO;
        uint32_t m_VBO;
        uint32_t m_EBO;
        uint32_t m_IndexCount;
    };
}

#endif // RENDERING__GEOMETRY__GPU_MESH_OPENGL__HPP
