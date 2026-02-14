#include "../include/TextRendererOpenGL.hpp"

#define STB_EASY_FONT_IMPLEMENTATION
#include "Utils/stb/include/stb_easy_font.h"
#include "pch.hpp"

#include "spdlog/spdlog.h"
#include "glad/gl.h"

namespace Andromeda::Rendering
{
    TextRendererOpenGL::TextRendererOpenGL()
        : m_VAO{ 0 }
        , m_VBO{ 0 }
        , m_isInitialized{ false }
    {
    }

    TextRendererOpenGL::~TextRendererOpenGL()
    {
        Destroy();
    }

    TextRendererOpenGL::TextRendererOpenGL(TextRendererOpenGL&& other) noexcept
        : m_VAO{ 0 }
        , m_VBO{ 0 }
        , m_isInitialized{ false }
    {
        MoveFrom(other);
    }

    TextRendererOpenGL& TextRendererOpenGL::operator=(TextRendererOpenGL&& other) noexcept
    {
        if (this != &other)
        {
            Destroy();
            MoveFrom(other);
        }
        return *this;
    }

    void TextRendererOpenGL::MoveFrom(TextRendererOpenGL& other) noexcept
    {
        m_VAO = other.m_VAO;
        m_VBO = other.m_VBO;
        m_isInitialized = other.m_isInitialized;

        other.m_VAO = 0;
        other.m_VBO = 0;
        other.m_isInitialized = false;
    }

    void TextRendererOpenGL::Destroy()
    {
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

        m_isInitialized = false;
    }

    bool TextRendererOpenGL::IsValid() const
    {
        return m_isInitialized && m_VAO != 0 && m_VBO != 0;
    }

    void TextRendererOpenGL::Init()
    {
        if (m_isInitialized)
        {
            return;
        }

        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);

        if (m_VAO == 0 || m_VBO == 0)
        {
            spdlog::error("TextRendererOpenGL::Init -> VAO or VBO is 0. GL context valid?");
        }

        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(
            0,
            2,
            GL_FLOAT,
            GL_FALSE,
            static_cast<GLsizei>(sizeof(float) * 2),
            reinterpret_cast<void*>(0)
        );

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        m_isInitialized = true;
    }

    void TextRendererOpenGL::RenderText(const std::string& text, float x, float y, float scale)
    {
        if (!m_isInitialized)
        {
            spdlog::warn("TextRendererOpenGL::RenderText called before Init()");
            return;
        }

        if (text.empty())
        {
            return;
        }

        // stb_easy_font outputs an array of vertices with a specific layout:
        //   struct stb_easy_font_vertex { float x,y,z; unsigned char color[4]; };
        // We replicate that layout here.
        struct EasyFontVertex
        {
            float x;
            float y;
            float z;
            unsigned char color[4];
        };

        static const int MAX_QUADS = 1024;
        EasyFontVertex quadBuffer[MAX_QUADS * 4]; // 4 verts per quad

        int numQuads = stb_easy_font_print(
            x,
            y,
            const_cast<char*>(text.c_str()),
            nullptr,                    // we ignore per-vertex color
            quadBuffer,
            sizeof(quadBuffer)
        );

        if (numQuads <= 0)
        {
            return;
        }

        if (numQuads > MAX_QUADS)
        {
            numQuads = MAX_QUADS;
        }

        // We will convert quads to triangles (2 per quad = 6 verts)
        std::vector<float> vertices;
        vertices.reserve(static_cast<std::size_t>(numQuads) * 6U * 2U);

        const float sx = scale;
        const float sy = scale;

        for (int i = 0; i < numQuads; ++i)
        {
            EasyFontVertex* q = quadBuffer + i * 4;

            float x0 = q[0].x * sx;
            float y0 = q[0].y * sy;
            float x1 = q[1].x * sx;
            float y1 = q[1].y * sy;
            float x2 = q[2].x * sx;
            float y2 = q[2].y * sy;
            float x3 = q[3].x * sx;
            float y3 = q[3].y * sy;

            // Two triangles: (v0, v1, v2) and (v0, v2, v3)
            float tri[6 * 2] =
            {
                x0, y0,
                x1, y1,
                x2, y2,

                x0, y0,
                x2, y2,
                x3, y3
            };

            vertices.insert(vertices.end(), tri, tri + 12);
        }

        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

        glBufferData(
            GL_ARRAY_BUFFER,
            static_cast<GLsizeiptr>(vertices.size() * sizeof(float)),
            vertices.data(),
            GL_DYNAMIC_DRAW
        );

        glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertices.size() / 2));

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void TextRendererOpenGL::RenderDebugQuad(
        float x,
        float y,
        float w,
        float h
    )
    {
        if (!m_isInitialized)
        {
            spdlog::warn("TextRendererOpenGL::RenderDebugQuad called before Init()");
            return;
        }

        float vertices[6 * 2] =
        {
            x,      y,
            x + w,  y,
            x + w,  y + h,

            x,      y,
            x + w,  y + h,
            x,      y + h
        };

        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

        glBufferData(
            GL_ARRAY_BUFFER,
            static_cast<GLsizeiptr>(sizeof(vertices)),
            vertices,
            GL_DYNAMIC_DRAW
        );

        glDrawArrays(GL_TRIANGLES, 0, 6);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
}
