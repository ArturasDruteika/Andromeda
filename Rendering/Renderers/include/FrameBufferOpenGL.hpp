#ifndef RENDERER__FRAME_BUFFER_OPENGL__HPP
#define RENDERER__FRAME_BUFFER_OPENGL__HPP


#include "pch.hpp"


namespace Andromeda::Rendering
{
    enum class FrameBufferType
    {
        None,
        Color,
        Depth,
        ColorDepth
    };


    class FrameBufferOpenGL
    {
    public:


    public:
        FrameBufferOpenGL() = default;
        FrameBufferOpenGL(int width, int height, FrameBufferType type);
        ~FrameBufferOpenGL();

        FrameBufferOpenGL(const FrameBufferOpenGL& other) = delete;
        FrameBufferOpenGL& operator=(const FrameBufferOpenGL& other) = delete;
        FrameBufferOpenGL(FrameBufferOpenGL&& other) noexcept;
        FrameBufferOpenGL& operator=(FrameBufferOpenGL&& other) noexcept;

        bool Init(int width, int height, FrameBufferType type);
        void Resize(int width, int height);

        void Bind() const;
        static void Unbind();

        // Getters
        unsigned int GetId() const;
        unsigned int GetColorTexture() const;     // valid only for ColorDepth
        unsigned int GetDepthRenderbuffer() const; // valid only for ColorDepth
        unsigned int GetDepthTexture() const;     // valid only for DepthOnly
        int GetWidth() const;
        int GetHeight() const;
        FrameBufferType GetFrameBufferType() const;

    private:
        void Destroy();
        bool Build();
        bool BuildColorDepth();
        bool BuildDepthOnly();
        bool CheckStatus() const;

    private:
        unsigned int m_FBO;
        unsigned int m_colorTex;
        unsigned int m_depthRBO;
        unsigned int m_depthTex;

        int m_width;
        int m_height;
        FrameBufferType m_type;
    };
}


#endif // RENDERER__FRAME_BUFFER_OPENGL__HPP