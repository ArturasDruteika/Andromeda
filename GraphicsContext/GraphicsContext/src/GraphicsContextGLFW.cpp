#include "../include/GraphicsContextGLFW.hpp"
#include "Window/WindowGLFW/include/WindowGLFW.hpp"
#include "spdlog/spdlog.h"

namespace Andromeda::GraphicsContext
{
    GraphicsContextGLFW::GraphicsContextGLFW()
        : m_initialized{ false }
        , m_pGLFWwindow{ nullptr }
    {
    }

    GraphicsContextGLFW::~GraphicsContextGLFW() = default;

    bool GraphicsContextGLFW::IsInitialized() const
    {
        return m_initialized;
    }

    bool GraphicsContextGLFW::Init(IWindow& window)
    {
        // We only support GLFW-based windows here
        Window::WindowGLFW* pWindowGLFW = dynamic_cast<Window::WindowGLFW*>(&window);
        if (pWindowGLFW == nullptr)
        {
            spdlog::error("GraphicsContextGLFW::Init - Invalid window type (expected WindowGLFW).");
            return false;
        }

        m_pGLFWwindow = static_cast<GLFWwindow*>(pWindowGLFW->GetNativeHandle());
        if (!m_pGLFWwindow)
        {
            spdlog::error("GraphicsContextGLFW::Init - GLFWwindow* is null.");
            return false;
        }

        // Make context current BEFORE loading GLAD
        glfwMakeContextCurrent(m_pGLFWwindow);

        if (glfwGetCurrentContext() == nullptr)
        {
            spdlog::error("GraphicsContextGLFW::Init - Failed to make OpenGL context current.");
            return false;
        }

        // Optional: context hints usually belong before window creation,
        // but if you want to keep them here, it's harmless for now.
        SetContextHints();

        if (!LoadGlad())
        {
            spdlog::error("GraphicsContextGLFW::Init - LoadGlad() failed.");
            return false;
        }

        m_initialized = true;
        return true;
    }

    void GraphicsContextGLFW::MakeCurrent()
    {
        if (!m_initialized || !m_pGLFWwindow)
        {
            spdlog::warn("GraphicsContextGLFW::MakeCurrent called but context is not initialized.");
            return;
        }

        glfwMakeContextCurrent(m_pGLFWwindow);

        if (glfwGetCurrentContext() == nullptr)
        {
            spdlog::error("GraphicsContextGLFW::MakeCurrent - Failed to make OpenGL context current.");
        }
    }

    void GraphicsContextGLFW::Present()
    {
        if (!m_initialized || !m_pGLFWwindow)
        {
            spdlog::warn("GraphicsContextGLFW::Present called but context is not initialized.");
            return;
        }

        glfwSwapBuffers(m_pGLFWwindow);
    }

    void GraphicsContextGLFW::SetContextHints()
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required on macOS
#endif
    }

    bool GraphicsContextGLFW::LoadGlad()
    {
        int gladVersion = gladLoadGL(glfwGetProcAddress);
        if (gladVersion == 0)
        {
            spdlog::error("GraphicsContextGLFW::LoadGlad - Failed to initialize GLAD (gladLoadGL returned 0).");
            return false;
        }

        spdlog::info(
            "GLAD loaded OpenGL {}.{}",
            GLAD_VERSION_MAJOR(gladVersion),
            GLAD_VERSION_MINOR(gladVersion)
        );

        const char* version = reinterpret_cast<const char*>(glGetString(GL_VERSION));
        if (version)
        {
            spdlog::info("OpenGL version string: {}", std::string(version));
        }
        else
        {
            spdlog::warn("OpenGL version string is null (glGetString(GL_VERSION) failed).");
        }

        return true;
    }
}
