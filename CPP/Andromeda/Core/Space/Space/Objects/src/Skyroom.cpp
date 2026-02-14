#include "../include/Skyroom.hpp"
#include "spdlog/spdlog.h"

namespace Andromeda::Space
{
    Skyroom::Skyroom(float halfExtent, const Color& color)
        : GeometricObject(color)
        , m_halfExtent(halfExtent)
    {
        ConstructSkyroom(m_halfExtent, color);
    }

    Skyroom::~Skyroom() = default;

    float Skyroom::GetHalfExtent() const
    {
        return m_halfExtent;
    }

    void Skyroom::SetHalfExtent(float halfExtent)
    {
        ValidateSkyroomParams(halfExtent);

        if (halfExtent <= 0.0f)
        {
            spdlog::error("Skyroom half-extent must be greater than zero. Given half-extent: {}", halfExtent);
            return;
        }

        m_halfExtent = halfExtent;
        ConstructSkyroom(m_halfExtent, GetColor());
    }

    void Skyroom::ValidateSkyroomParams(float halfExtent) const
    {
        (void)halfExtent;
        // You can clamp/abs here if you want; I keep it strict like Sphere/Cube.
    }

    void Skyroom::ConstructSkyroom(float halfExtent, const Color& color)
    {
        if (halfExtent <= 0.0f)
        {
            spdlog::error("Skyroom half-extent must be greater than zero. Given half-extent: {}", halfExtent);
            return;
        }

        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        ReserveSkyroomBuffers(vertices, indices);

        std::array<SkyroomFaceData, 6> faces = BuildSkyroomFaces(halfExtent);

        unsigned int indexOffset = 0;
        for (const SkyroomFaceData& face : faces)
        {
            AppendFaceInside(face, color, vertices, indices, indexOffset);
        }

        Mesh mesh;
        mesh.SetData(vertices, indices);

        SetMesh(mesh);
    }

    std::array<SkyroomFaceData, 6> Skyroom::BuildSkyroomFaces(float halfExtent)
    {
        // Inward normals (pointing toward center) and vertex order chosen for inside-facing triangles.
        // This is basically the cube, but normals flipped and winding appropriate for inside view.

        return std::array<SkyroomFaceData, 6>
        {
            SkyroomFaceData
            {
                Math::Vec3(0.0f, 0.0f, 1.0f), // inward for back (-Z)
                {
                    Math::Vec3(-halfExtent, -halfExtent, -halfExtent),
                    Math::Vec3(halfExtent, -halfExtent, -halfExtent),
                    Math::Vec3(halfExtent,  halfExtent, -halfExtent),
                    Math::Vec3(-halfExtent,  halfExtent, -halfExtent)
                }
            },

            SkyroomFaceData
            {
                Math::Vec3(0.0f, 0.0f, -1.0f), // inward for front (+Z)
                {
                    Math::Vec3(-halfExtent, -halfExtent,  halfExtent),
                    Math::Vec3(-halfExtent,  halfExtent,  halfExtent),
                    Math::Vec3(halfExtent,  halfExtent,  halfExtent),
                    Math::Vec3(halfExtent, -halfExtent,  halfExtent)
                }
            },

            SkyroomFaceData
            {
                Math::Vec3(1.0f, 0.0f, 0.0f), // inward for left (-X)
                {
                    Math::Vec3(-halfExtent, -halfExtent, -halfExtent),
                    Math::Vec3(-halfExtent,  halfExtent, -halfExtent),
                    Math::Vec3(-halfExtent,  halfExtent,  halfExtent),
                    Math::Vec3(-halfExtent, -halfExtent,  halfExtent)
                }
            },

            SkyroomFaceData
            {
                Math::Vec3(-1.0f, 0.0f, 0.0f), // inward for right (+X)
                {
                    Math::Vec3(halfExtent, -halfExtent, -halfExtent),
                    Math::Vec3(halfExtent, -halfExtent,  halfExtent),
                    Math::Vec3(halfExtent,  halfExtent,  halfExtent),
                    Math::Vec3(halfExtent,  halfExtent, -halfExtent)
                }
            },

            SkyroomFaceData
            {
                Math::Vec3(0.0f, 1.0f, 0.0f), // inward for bottom (-Y)
                {
                    Math::Vec3(-halfExtent, -halfExtent, -halfExtent),
                    Math::Vec3(-halfExtent, -halfExtent,  halfExtent),
                    Math::Vec3(halfExtent, -halfExtent,  halfExtent),
                    Math::Vec3(halfExtent, -halfExtent, -halfExtent)
                }
            },

            SkyroomFaceData
            {
                Math::Vec3(0.0f, -1.0f, 0.0f), // inward for top (+Y)
                {
                    Math::Vec3(-halfExtent,  halfExtent, -halfExtent),
                    Math::Vec3(halfExtent,  halfExtent, -halfExtent),
                    Math::Vec3(halfExtent,  halfExtent,  halfExtent),
                    Math::Vec3(-halfExtent,  halfExtent,  halfExtent)
                }
            }
        };
    }

    void Skyroom::ReserveSkyroomBuffers(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
    {
        vertices.reserve(24);
        indices.reserve(36);
    }

    void Skyroom::AppendFaceInside(
        const SkyroomFaceData& face,
        const Color& color,
        std::vector<Vertex>& outVertices,
        std::vector<unsigned int>& outIndices,
        unsigned int& indexOffset
    )
    {
        for (const Math::Vec3& pos : face.vertices)
        {
            outVertices.emplace_back(pos, color, face.normal);
        }

        // Same quad split as Cube. Winding is determined by vertex order in BuildSkyroomFaces.
        outIndices.push_back(indexOffset + 0);
        outIndices.push_back(indexOffset + 1);
        outIndices.push_back(indexOffset + 2);

        outIndices.push_back(indexOffset + 2);
        outIndices.push_back(indexOffset + 3);
        outIndices.push_back(indexOffset + 0);

        indexOffset += 4;
    }
}
