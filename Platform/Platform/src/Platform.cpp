#include "../include/Platform.hpp"
#include "glad/gl.h"
#include "GLFWWindow.hpp"
#include "GLFWContext.hpp"
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

        m_pContext = std::make_unique<Context::GLFWContext>();
        m_pContext->Init();

        m_pWindow = std::make_unique<Window::GLFWWindow>(width, height, title, true);
        if (!m_pWindow)
        {
            spdlog::error("Failed to create GLFW window.");
            glfwTerminate();
            return false;
        }

        m_pContext->MakeContextCurrent(m_pWindow->GetWindow());

        // === GLAD v2: load OpenGL function pointers ===
        // gladLoadGL takes a loader function: (const char* name) -> void*
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
        // ==============================================

        m_pWindow->SetCallbackFunctions();

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
            m_pWindow->DeInit();
            m_pWindow = nullptr;
        }

        m_pContext->TerminateGLFW();
        m_initialized = false;

        spdlog::info("Platform shutdown completed.");
    }

    void Platform::PollEvents() const
    {
        if (!m_initialized)
        {
            return;
        }

        glfwPollEvents();
    }

    bool Platform::ShouldClose() const
    {
        if (!m_pWindow)
        {
            return true;
        }

        return glfwWindowShouldClose(m_pWindow->GetWindow()) != 0;
    }

    void Platform::SwapBuffers() const
    {
        if (m_pWindow)
        {
            glfwSwapBuffers(m_pWindow->GetWindow());
        }
    }

    int Platform::GetWindowWidth() const
    {
        return m_width;
    }

    int Platform::GetWindowHeight() const
    {
        return m_height;
    }

    GLFWwindow* Platform::GetNativeWindow() const
    {
        return m_pWindow->GetWindow();
    }
}