#include "../include/FrameBufferOpenGL.hpp"
#include "glad/gl.h"
#include "spdlog/spdlog.h"


namespace Andromeda::Rendering
{
    FrameBufferOpenGL::FrameBufferOpenGL()
        : m_FBO{ 0 }
        , m_colorTex{ 0 }
        , m_depthRBO{ 0 }
        , m_depthTex{ 0 }
		, m_depthCubeTex{ 0 }
        , m_width{ 0 }
        , m_height{ 0 }
        , m_type{ FrameBufferType::None }
    {
    }

    FrameBufferOpenGL::FrameBufferOpenGL(int width, int height, FrameBufferType type)
        : m_FBO{ 0 }
        , m_colorTex{ 0 }
        , m_depthRBO{ 0 }
        , m_depthTex{ 0 }
		, m_depthCubeTex{ 0 }
        , m_width{ width }
        , m_height{ height }
        , m_type{ type }
    {
        Init(width, height, type);
    }


    FrameBufferOpenGL::~FrameBufferOpenGL()
    {
        Destroy();
    }

    FrameBufferOpenGL::FrameBufferOpenGL(FrameBufferOpenGL&& other) noexcept
    {
        *this = std::move(other);
    }

    FrameBufferOpenGL& FrameBufferOpenGL::operator=(FrameBufferOpenGL&& other) noexcept
    {
        if (this == &other)
            return *this;

        Destroy();

        m_FBO = other.m_FBO;
        m_colorTex = other.m_colorTex;
        m_depthRBO = other.m_depthRBO;
        m_depthTex = other.m_depthTex;
		m_depthCubeTex = other.m_depthCubeTex;
        m_width = other.m_width;
        m_height = other.m_height;
        m_type = other.m_type;

        other.m_FBO = 0;
        other.m_colorTex = 0;
        other.m_depthRBO = 0;
        other.m_depthTex = 0;
		other.m_depthCubeTex = 0;
        other.m_width = 0;
        other.m_height = 0;

        return *this;
    }

    bool FrameBufferOpenGL::Init(int width, int height, FrameBufferType type)
    {
        Destroy();

        m_width = width;
        m_height = height;
        m_type = type;

        if (m_width <= 0 || m_height <= 0)
        {
            spdlog::error("FrameBufferOpenGL::Init: invalid size {}x{}", m_width, m_height);
            return false;
        }

        return Build();
    }

    void FrameBufferOpenGL::Resize(int width, int height)
    {
        if (width == m_width && height == m_height)
            return;

        Init(width, height, m_type);
    }

    void FrameBufferOpenGL::Bind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
    }

    void FrameBufferOpenGL::Unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    unsigned int FrameBufferOpenGL::GetId() const
    {
        return m_FBO;
    }

    unsigned int FrameBufferOpenGL::GetColorTexture() const
    {
        return m_colorTex;
    }

    unsigned int FrameBufferOpenGL::GetDepthRenderbuffer() const
    {
        return m_depthRBO;
    }

    unsigned int FrameBufferOpenGL::GetDepthTexture() const
    {
        return m_depthTex;
    }

    unsigned int FrameBufferOpenGL::GetDepthCubeTexture() const
    {
        return m_depthCubeTex;
    }

    int FrameBufferOpenGL::GetWidth() const
    {
        return m_width;
    }

    int FrameBufferOpenGL::GetHeight() const
    {
        return m_height;
    }

    FrameBufferType FrameBufferOpenGL::GetFrameBufferType() const
    {
        return m_type;
    }

    void FrameBufferOpenGL::Destroy()
    {
        if (m_colorTex)
        {
            glDeleteTextures(1, &m_colorTex);
            m_colorTex = 0;
        }
        if (m_depthTex)
        {
            glDeleteTextures(1, &m_depthTex);
            m_depthTex = 0;
        }
        if (m_depthRBO)
        {
            glDeleteRenderbuffers(1, &m_depthRBO);
            m_depthRBO = 0;
        }
        if (m_FBO)
        {
            glDeleteFramebuffers(1, &m_FBO);
            m_FBO = 0;
        }
        if (m_depthCubeTex)
        {
            glDeleteTextures(1, &m_depthCubeTex);
            m_depthCubeTex = 0;
        }
    }

    bool FrameBufferOpenGL::Build()
    {
        switch (m_type)
        {
        case FrameBufferType::ColorDepth:
            return BuildColorDepth();
        case FrameBufferType::Depth:
            return BuildDepthOnly();
		case FrameBufferType::DepthCube:
            return BuildDepthCube();
        default:
            spdlog::error("FrameBufferOpenGL::Build: unknown type");
            return false;
        }
    }

    bool FrameBufferOpenGL::BuildColorDepth()
    {
        glGenFramebuffers(1, &m_FBO);
        glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

        // Create color texture
        glGenTextures(1, &m_colorTex);
        glBindTexture(GL_TEXTURE_2D, m_colorTex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colorTex, 0);

        // Create depth renderbuffer
        glGenRenderbuffers(1, &m_depthRBO);
        glBindRenderbuffer(GL_RENDERBUFFER, m_depthRBO);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, m_width, m_height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthRBO);

        GLenum drawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
        glDrawBuffers(1, drawBuffers);

        bool ok = CheckStatus();
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        return ok;
    }

    bool FrameBufferOpenGL::BuildDepthOnly()
    {
        glGenFramebuffers(1, &m_FBO);
        glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

        glGenTextures(1, &m_depthTex);
        glBindTexture(GL_TEXTURE_2D, m_depthTex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, m_width, m_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

        float borderColor[] = { 1, 1, 1, 1 };
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthTex, 0);

        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);

        bool ok = CheckStatus();
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        return ok;
    }

    bool FrameBufferOpenGL::BuildDepthCube()
    {
        glGenFramebuffers(1, &m_FBO);
        glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

        glGenTextures(1, &m_depthCubeTex);
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_depthCubeTex);

        // kill mipmap ambiguity across resizes
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_BASE_LEVEL, 0);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_LEVEL, 0);

        // safer internal format/type pairing for depth
        for (int i = 0; i < 6; ++i)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0,
                GL_DEPTH_COMPONENT32F,     // <-- use 32F for GL_FLOAT
                m_width, 
                m_height,
                0,
                GL_DEPTH_COMPONENT,
                GL_FLOAT,
                nullptr);
            // If you prefer 24-bit: internal=GL_DEPTH_COMPONENT24, type=GL_UNSIGNED_INT
        }

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        // attach the WHOLE cubemap (layered)
        glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_depthCubeTex, 0);

        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);

        bool ok = CheckStatus();               // checks the currently bound FBO
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        return ok;
    }

    bool FrameBufferOpenGL::CheckStatus() const
    {
        GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (status != GL_FRAMEBUFFER_COMPLETE)
        {
            spdlog::error("Framebuffer not complete! Status: 0x{:X}", status);
            return false;
        }
        return true;
    }
}
