#include "../include/Platform.hpp"
#include "GraphicsContext/include/GraphicsContextGLFW.hpp"
#include "Window/WindowGLFW/include/WindowGLFW.hpp"
#include "Window/Events/include/EventDispatcher.hpp"
#include "Window/Events/include/FrameBufferEvents.hpp"
#include "spdlog/spdlog.h"


namespace Andromeda::Platform
{
    Platform::Platform(const GraphicsBackend& graphicsBackend)
        : m_initialized{ false }
        , m_graphicsBackend{ graphicsBackend }
    {
    }

    Platform::~Platform()
    {
        Shutdown();
    }

    bool Platform::IsInitialized() const
    {
        return m_initialized;
    }

    GraphicsBackend Platform::GetGraphicsBackend() const
    {
        return m_graphicsBackend;
    }

    bool Platform::Init(int width, int height, const std::string& title)
    {
        if (m_initialized)
        {
            spdlog::warn("Platform::Init() called but platform is already initialized.");
            return true;
        }

        spdlog::info(
            "Platform::Init() starting for backend {}",
            GraphicsBackendString(m_graphicsBackend)
        );

        // GLFW init is shared for now (OpenGL / Vulkan both need it in your current setup)
        if (!glfwInit())
        {
            spdlog::error("Platform::Init() - Failed to initialize GLFW.");
            return false;
        }

        try
        {
            CreateWindow(width, height, title);
            if (!m_pWindow)
            {
                spdlog::error("Platform::Init() failed: window creation returned nullptr.");
                glfwTerminate();
                return false;
            }

            CreateGraphicsContext();
            if (!m_pGraphicsContext)
            {
                spdlog::error("Platform::Init() failed: graphics context creation returned nullptr.");
                m_pWindow.reset();
                glfwTerminate();
                return false;
            }

            m_pGraphicsContext->Init(*m_pWindow);
            m_pGraphicsContext->MakeCurrent();

            m_pWindow->SetEventCallback(
                [this](IEvent& e)
                {
                    // Option A: just pass to engine / application
                    // m_Engine->OnEvent(e);

                    // Option B: handle some platform-level stuff here
                    Window::EventDispatcher dispatcher(e);

                    dispatcher.Dispatch<Window::WindowCloseEvent>(
                        [this](Window::WindowCloseEvent& evt)
                        {
                            // maybe tell engine to stop, etc.
                            return true;
                        });

                    // You can still forward to engine:
                    // m_Engine->OnEvent(e);
                }
            );

            m_initialized = true;
            spdlog::info("Platform::Init() succeeded.");
            return true;
        }
        catch (const std::exception& ex)
        {
            spdlog::error("Exception during Platform::Init(): {}", ex.what());
        }
        catch (...)
        {
            spdlog::error("Unknown exception during Platform::Init().");
        }

        // Clean up on failure
        m_pGraphicsContext.reset();
        m_pWindow.reset();
        glfwTerminate();
        return false;
    }

    void Platform::Shutdown()
    {
        if (!m_initialized)
        {
            return;
        }

        spdlog::info("Platform::Shutdown() starting.");

        // Destroy window and context; GLFWWindow internally destroys GLFWwindow.
        if (m_pGraphicsContext)
        {
            // no explicit DeInit on context for now; RAII via destructor
            m_pGraphicsContext.reset();
        }

        if (m_pWindow)
        {
            m_pWindow.reset();
        }

        glfwTerminate();

        m_initialized = false;
        spdlog::info("Platform shutdown completed.");
    }

    IGraphicsContext* Platform::GetGraphicsContext() const
    {
        if (!m_pGraphicsContext)
        {
            spdlog::warn("Platform::GetGraphicsContext() called but graphics context is nullptr.");
        }
        return m_pGraphicsContext.get();
    }

    IWindow* Platform::GetWindow() const
    {
        if (!m_pWindow)
        {
            spdlog::warn("Platform::GetWindow() called but window is nullptr.");
        }
        return m_pWindow.get();
    }

    void Platform::CreateWindow(int width, int height, const std::string& title)
    {
        spdlog::info(
            "Platform::CreateWindow() for backend {}",
            GraphicsBackendString(m_graphicsBackend)
        );

        try
        {
            switch (m_graphicsBackend)
            {
            case GraphicsBackend::OpenGL:
            case GraphicsBackend::Vulkan:
                // For now both use GLFWWindow
                m_pWindow = std::make_unique<Window::WindowGLFW>(width, height, title, true);
                if (!m_pWindow)
                {
                    spdlog::error("Platform::CreateWindow() - WindowGLFW creation returned nullptr.");
                }
                break;

            case GraphicsBackend::None:
            default:
                spdlog::error(
                    "Platform::CreateWindow(): Unsupported graphics backend {}.",
                    GraphicsBackendString(m_graphicsBackend)
                );
                m_pWindow.reset();
                break;
            }
        }
        catch (const std::exception& ex)
        {
            spdlog::error("Exception in Platform::CreateWindow(): {}", ex.what());
            m_pWindow.reset();
        }
        catch (...)
        {
            spdlog::error("Unknown exception in Platform::CreateWindow().");
            m_pWindow.reset();
        }
    }

    void Platform::CreateGraphicsContext()
    {
        spdlog::info(
            "Platform::CreateGraphicsContext() for backend {}",
            GraphicsBackendString(m_graphicsBackend)
        );

        try
        {
            switch (m_graphicsBackend)
            {
            case GraphicsBackend::OpenGL:
                m_pGraphicsContext = std::make_unique<GraphicsContext::GraphicsContextGLFW>();
                spdlog::info("Platform::CreateGraphicsContext() created OpenGL (GLFW) graphics context.");
                break;

            case GraphicsBackend::Vulkan:
                spdlog::warn("Platform::CreateGraphicsContext(): Vulkan backend not implemented yet.");
                m_pGraphicsContext.reset();
                break;

            case GraphicsBackend::None:
            default:
                spdlog::error(
                    "Platform::CreateGraphicsContext(): Unsupported graphics backend {}.",
                    GraphicsBackendString(m_graphicsBackend)
                );
                m_pGraphicsContext.reset();
                break;
            }
        }
        catch (const std::exception& ex)
        {
            spdlog::error("Exception in Platform::CreateGraphicsContext(): {}", ex.what());
            m_pGraphicsContext.reset();
        }
        catch (...)
        {
            spdlog::error("Unknown exception in Platform::CreateGraphicsContext().");
            m_pGraphicsContext.reset();
        }
    }
}

namespace Andromeda
{
    std::unique_ptr<IPlatform> CreatePlatform(const GraphicsBackend& graphicsBackend)
    {
        spdlog::info(
            "CreatePlatform() called with backend {}",
            GraphicsBackendString(graphicsBackend)
        );

        try
        {
            std::unique_ptr<IPlatform> platform = std::make_unique<Platform::Platform>(graphicsBackend);
            return platform;
        }
        catch (const std::exception& ex)
        {
            spdlog::error("Exception in CreatePlatform(): {}", ex.what());
        }
        catch (...)
        {
            spdlog::error("Unknown exception in CreatePlatform().");
        }

        return nullptr;
    }
}
