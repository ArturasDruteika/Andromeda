#include "../include/SkyroomOpenGLImpl.hpp"
#include "Space/Vertices/include/Vertex.hpp"
#include "glad/gl.h"


namespace Andromeda::Rendering
{
    // Build CCW triangles as seen from INSIDE the cube; normals point inward.
    static inline void PushTri(std::vector<Space::Vertex>& v,
        const Space::Point3D& a,
        const Space::Point3D& b,
        const Space::Point3D& c,
        const Math::Vec3& n,
        const Space::Color& col)
    {
        v.emplace_back(a, col, n);
        v.emplace_back(b, col, n);
        v.emplace_back(c, col, n);
    }

    SkyroomOpenGL::SkyroomOpenGLImpl::SkyroomOpenGLImpl(const Math::Vec3& centerPosition, float halfExtent, const Space::Color& color)
        : RenderableObjectOpenGL(
            centerPosition,
            color,
            std::vector{
                VertexAttributes{ 0, Space::Point3D::Size(), GL_FLOAT, GL_FALSE, sizeof(Space::Vertex), 0 }, // Position
                VertexAttributes{ 1, Space::Color::Size(), GL_FLOAT, GL_FALSE, sizeof(Space::Vertex), sizeof(Space::Point3D)}, // Color
                VertexAttributes{ 2, Math::Vec3::Size(), GL_FLOAT, GL_FALSE, sizeof(Space::Vertex), sizeof(Space::Point3D) + sizeof(Space::Color)} // Normal
            }
        )
        , m_halfExtent{ halfExtent }
    {
        BuildGeometry(halfExtent, { -1.f, 0.f, 0.f });
        Translate(centerPosition);
        Init(); // uploads VBO/VAO/EBO using your base helpers
    }

    SkyroomOpenGL::SkyroomOpenGLImpl::~SkyroomOpenGLImpl() = default;

    float SkyroomOpenGL::SkyroomOpenGLImpl::GetHalfExtent() const
    {
        return m_halfExtent;
	}

    void SkyroomOpenGL::SkyroomOpenGLImpl::BuildGeometry(float h, const Space::Color& colorGray)
    {
        // 8 corners
        const Space::Point3D p[8] = {
            { -h, -h, -h }, { +h, -h, -h }, { +h, +h, -h }, { -h, +h, -h },
            { -h, -h, +h }, { +h, -h, +h }, { +h, +h, +h }, { -h, +h, +h }
        };

        m_vertices.clear();
        m_indices.clear();
        m_vertices.reserve(36);

        // +X face (inward normal -X)
        PushTri(m_vertices, p[2], p[6], p[5], { -1.f, 0.f, 0.f }, colorGray);
        PushTri(m_vertices, p[2], p[5], p[1], { -1.f, 0.f, 0.f }, colorGray);

        // -X face (inward normal +X)
        PushTri(m_vertices, p[7], p[3], p[0], { +1.f, 0.f, 0.f }, colorGray);
        PushTri(m_vertices, p[7], p[0], p[4], { +1.f, 0.f, 0.f }, colorGray);

        // +Y face (inward normal -Y)
        PushTri(m_vertices, p[3], p[7], p[6], { 0.f, -1.f, 0.f }, colorGray);
        PushTri(m_vertices, p[3], p[6], p[2], { 0.f, -1.f, 0.f }, colorGray);

        // -Y face (inward normal +Y)
        PushTri(m_vertices, p[4], p[0], p[1], { 0.f, +1.f, 0.f }, colorGray);
        PushTri(m_vertices, p[4], p[1], p[5], { 0.f, +1.f, 0.f }, colorGray);

        // +Z face (inward normal -Z)
        PushTri(m_vertices, p[6], p[7], p[4], { 0.f, 0.f, -1.f }, colorGray);
        PushTri(m_vertices, p[6], p[4], p[5], { 0.f, 0.f, -1.f }, colorGray);

        // -Z face (inward normal +Z)
        PushTri(m_vertices, p[0], p[3], p[2], { 0.f, 0.f, +1.f }, colorGray);
        PushTri(m_vertices, p[0], p[2], p[1], { 0.f, 0.f, +1.f }, colorGray);

        // indices 0..N-1
        m_indices.resize(m_vertices.size());
        for (unsigned int i = 0; i < m_indices.size(); ++i)
        {
            m_indices[i] = i;
        }
    }
}
