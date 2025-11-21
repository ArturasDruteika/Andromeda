#include "../include/Platform.hpp"
#include "glad/gl.h"
#include "Window/WindowGLFW/include/WindowGLFW.hpp"
#include "GraphicsContext/include/GraphicsContextGLFW.hpp"
#include "spdlog/spdlog.h"


namespace Andromeda::Platform
{
    Platform::Platform()
        : m_pWindow{ nullptr }
        , m_width{ 0 }
        , m_height{ 0 }
        , m_initialized{ false }
    {
    }

    Platform::~Platform()
    {
        Shutdown();
    }

    bool Platform::Init(int width, int height, const std::string& title)
    {
        if (m_initialized)
        {
            spdlog::warn("Platform::Init() called but platform is already initialized.");
            return true;
        }

        if (!glfwInit())
        {
            spdlog::error("Failed to initialize GLFW.");
            return false;
        }

        m_pWindow = std::make_unique<Window::WindowGLFW>(width, height, title, true);
        if (!m_pWindow)
        {
            spdlog::error("Failed to create GLFW window.");
            glfwTerminate();
            return false;
        }

        m_pGraphicsContext = std::make_unique<GraphicsContext::GraphicsContextGLFW>();
        m_pGraphicsContext->Init(*m_pWindow);
        m_pGraphicsContext->MakeCurrent();

        int gladVersion = gladLoadGL(glfwGetProcAddress);
        if (gladVersion == 0)
        {
            spdlog::error("Failed to initialize GLAD (gladLoadGL returned 0).");
            glfwTerminate();
            return false;
        }

        spdlog::info(
            "GLAD loaded OpenGL {}.{}",
            GLAD_VERSION_MAJOR(gladVersion),
            GLAD_VERSION_MINOR(gladVersion)
        );

        //m_pWindow->SetCallbackFunctions();

        const char* version = reinterpret_cast<const char*>(glGetString(GL_VERSION));
        if (version)
        {
            spdlog::info("Platform initialized. OpenGL version string: {}", std::string(version));
        }
        else
        {
            spdlog::warn("Platform initialized, but could not query OpenGL version string.");
        }

        m_width = width;
        m_height = height;
        m_initialized = true;

        return true;
    }

    void Platform::Shutdown()
    {
        if (!m_initialized)
        {
            return;
        }

        if (m_pWindow)
        {
            //m_pWindow->DeInit();
            m_pWindow = nullptr;
        }

        //m_pGraphicsContext->TerminateGLFW();
        m_initialized = false;

        spdlog::info("Platform shutdown completed.");
    }

    void Platform::PollEvents() const
    {
		m_pWindow->PollEvents();
    }

    bool Platform::ShouldClose() const
    {
		return m_pWindow->ShouldClose();
    }

    void Platform::SwapBuffers() const
    {
        m_pGraphicsContext->Present();
    }

    int Platform::GetWindowWidth() const
    {
        return m_width;
    }

    int Platform::GetWindowHeight() const
    {
        return m_height;
    }

    IGraphicsContext* Platform::GetGraphicsContext() const
    {
        if (!m_pGraphicsContext)
        {
            spdlog::warn("GraphicsContext() called but graphics context is nullptr.");
        }
        return m_pGraphicsContext.get();
    }

    IWindow* Platform::GetWindow() const
    {
        if (!m_pWindow)
        {
            spdlog::warn("Window() called but window is nullptr.");
        }
        return m_pWindow.get();
    }

    //GLFWwindow* Platform::GetWindow() const
    //{
    //    return m_pWindow->GetWindow();
    //}
}