#include "../include/Application.hpp"
#include "Engine/Engine/include/Engine.hpp"

#include "spdlog/spdlog.h"


namespace Andromeda::Application
{
    Application::Application(GraphicsBackend graphicsBackend)
        : m_initialized{ false }
        , m_graphicsBackend{ graphicsBackend }
        , m_pPlatform{ nullptr }
        , m_pEngine{ nullptr }
        , m_pScene{ nullptr }
        , m_pWindow{ nullptr }
        , m_pContext{ nullptr }
        , m_pRenderer{ nullptr }
    {
    }

    Application::~Application()
    {
        if (m_initialized)
        {
            DeInit();
        }
    }

    IRenderer* Application::GetRenderer()
    {
        return m_pRenderer;
    }

    bool Application::Init(unsigned int width, unsigned int height, const std::string& title)
    {
        return InitInternal(width, height, title);
    }

    void Application::DeInit()
    {
        if (!m_pPlatform && !m_pEngine)
        {
            m_initialized = false;
            return;
        }

        // Engine teardown first (it may reference renderer/resources)
        if (m_pEngine)
        {
            m_pEngine->DeInit();
            m_pEngine.reset();
        }

        // Platform teardown last (destroys window/context)
        if (m_pPlatform)
        {
            m_pPlatform->Shutdown();
            m_pPlatform.reset();
        }

        m_pWindow = nullptr;
        m_pContext = nullptr;
        m_pRenderer = nullptr;
        m_pScene = nullptr;

        m_initialized = false;
    }

    void Application::SetScene(IScene* pScene)
    {
        m_pScene = pScene;

        // If your Engine has SetScene, call it here:
        // (You added Engine::SetScene(IScene*))
        if (m_pEngine)
        {
            // Engine::Engine has SetScene, but IEngine does not in your original API.
            // If you want this call through IEngine, add SetScene to IEngine too.
            // For now, dynamic_cast safely if needed:
            auto* pEngineImpl = dynamic_cast<Engine::Engine*>(m_pEngine.get());
            if (pEngineImpl)
            {
                pEngineImpl->SetScene(m_pScene);
            }
        }
    }

    int Application::Run()
    {
        if (!m_initialized)
        {
            spdlog::error("Application::Run() called but application is not initialized.");
            return -1;
        }

        if (!m_pScene)
        {
            spdlog::error("Application::Run() called but scene is null. Call SetScene() first.");
            return -1;
        }

        // Ensure engine sees the scene (if not already connected)
        if (m_pEngine)
        {
            Engine::Engine* pEngineImpl = dynamic_cast<Engine::Engine*>(m_pEngine.get());
            if (pEngineImpl)
            {
                pEngineImpl->SetScene(m_pScene);
            }
        }

        RenderLoop();
        
        return 0;
    }

    bool Application::InitPlatform(unsigned int width, unsigned int height, const std::string& title)
    {
        m_pPlatform = CreatePlatform(m_graphicsBackend);
        if (!m_pPlatform)
        {
            spdlog::error("CreatePlatform() returned nullptr.");
            return false;
        }

        if (!m_pPlatform->Init(width, height, title))
        {
            spdlog::error("Failed to initialize Platform.");
            return false;
        }

        return true;
    }

    bool Application::InitEngine()
    {
        m_pEngine = CreateEngine(m_graphicsBackend);
        if (!m_pEngine)
        {
            spdlog::error("CreateEngine() returned nullptr.");
            return false;
        }

        if (!m_pEngine->Init())
        {
            spdlog::error("Engine::Init() failed.");
            return false;
        }

        return true;
    }

    bool Application::InitRenderer(int width, int height)
    {
        // You had: pRenderer->Init(width, height, false);
        m_pRenderer->Init(width, height, false);
        return true;
    }

    bool Application::InitInternal(unsigned int width, unsigned int height, const std::string &title)
    {
        if (m_initialized)
        {
            spdlog::warn("Application::Init() called but application is already initialized.");
            return true;
        }

        if (!InitPlatform(width, height, title))
        {
            spdlog::error("Application::Init() failed: platform init failed.");
            return false;
        }

        if (!InitEngine())
        {
            spdlog::error("Application::Init() failed: engine init failed.");
            DeInit();
            return false;
        }

        m_pWindow = m_pPlatform->GetWindow();
        m_pContext = m_pPlatform->GetGraphicsContext();
        m_pRenderer = m_pEngine->GetRenderer();

        if (!m_pWindow || !m_pContext || !m_pRenderer)
        {
            spdlog::error("Application::Init() failed: window/context/renderer is null.");
            DeInit();
            return false;
        }

        ConnectEvents();

        if (!InitRenderer(static_cast<int>(width), static_cast<int>(height)))
        {
            spdlog::error("Application::Init() failed: renderer init failed.");
            DeInit();
            return false;
        }
        m_initialized = true;
        return true;
    }

    void Application::ConnectEvents()
    {
        // This is the thing you wanted hidden from main:
        // Window pushes IEvent -> Engine consumes it.
        m_pWindow->SetEventCallback([this](IEvent& e)
            {
                if (m_pEngine)
                {
                    m_pEngine->OnEvent(e);
                }
            });
    }

    void Application::RenderLoop()
    {
        while (!m_pWindow->ShouldClose())
        {
            m_pWindow->PollEvents();
            m_pRenderer->RenderFrame(*m_pScene);
            m_pContext->Present();
        }
    }
}


namespace Andromeda
{
    std::unique_ptr<IApplication> CreateApp(const GraphicsBackend& graphicsBackend)
    {
        spdlog::info(
            "CreateApplication() called with backend {}",
            GraphicsBackendString(graphicsBackend)
        );

        try
        {
            std::unique_ptr<IApplication> application = std::make_unique<Application::Application>(graphicsBackend);
            return application;
        }
        catch (const std::exception& ex)
        {
            spdlog::error("Exception in CreateApplication(): {}", ex.what());
        }
        catch (...)
        {
            spdlog::error("Unknown exception in CreateApplication().");
        }

        return nullptr;
    }
}

