#ifndef RENDERING__OPENGL__SUPPORT__TEXT_RENDERER_OPENGL__HPP
#define RENDERING__OPENGL__SUPPORT__TEXT_RENDERER_OPENGL__HPP


#include "glad/gl.h"

#include <string>


namespace Andromeda::Rendering
{
    class TextRendererOpenGL
    {
    public:
        TextRendererOpenGL();
        ~TextRendererOpenGL();

        TextRendererOpenGL(const TextRendererOpenGL& other) = delete;
        TextRendererOpenGL& operator=(const TextRendererOpenGL& other) = delete;
        TextRendererOpenGL(TextRendererOpenGL&& other) noexcept;
        TextRendererOpenGL& operator=(TextRendererOpenGL&& other) noexcept;

        // Initializes VAO/VBO for text vertices (vec2 positions).
        // Caller is responsible for binding a suitable shader and setting uniforms.
        void Init();

        // x, y are passed directly to stb_easy_font and then scaled on CPU.
        // The coordinate system is whatever your text shader expects (typically screen space).
        void RenderText(const std::string& text, float x, float y, float scale = 1.0f);
        void RenderDebugQuad(float x, float y, float w, float h);

        bool IsValid() const;

    private:
        void Destroy();
        void MoveFrom(TextRendererOpenGL& other) noexcept;

    private:
        bool m_isInitialized;
        GLuint m_VAO;
        GLuint m_VBO;
    };
}


#endif // RENDERING__OPENGL__SUPPORT__TEXT_RENDERER_OPENGL__HPP
