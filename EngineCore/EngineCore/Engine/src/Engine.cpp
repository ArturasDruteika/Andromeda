#include "../include/Engine.hpp"
#include "Rendering/Renderers/Renderers/include/RendererOpenGL.hpp"
#include "spdlog/spdlog.h"


namespace Andromeda::EngineCore
{
    Engine::Engine(const GraphicsBackend& graphicsBackend)
        : m_initialized{ false }
        , m_graphicsBackend{ graphicsBackend }
    {
        spdlog::info(
            "Engine constructed with graphics backend {}",
            GraphicsBackendString(m_graphicsBackend)
        );
    }

    Engine::~Engine()
    {
        if (m_initialized)
        {
            try
            {
                spdlog::info("Engine destructor: deinitializing engine.");
                DeInit();
            }
            catch (const std::exception& ex)
            {
                spdlog::error("Exception in Engine::~Engine during DeInit: {}", ex.what());
            }
            catch (...)
            {
                spdlog::error("Unknown exception in Engine::~Engine during DeInit.");
            }
        }
        else
        {
            spdlog::info("Engine destructor: engine was not initialized, nothing to deinitialize.");
        }
    }

    bool Engine::IsInitialized() const
    {
        return m_initialized;
    }

    GraphicsBackend Engine::GetGraphicsBackend() const
    {
        return m_graphicsBackend;
    }

    IRenderer* Engine::GetRenderer() const
    {
        if (!m_renderer)
        {
            spdlog::warn("Engine::GetRenderer() called but renderer is nullptr.");
        }
        return m_renderer.get();
    }

    bool Engine::Init()
    {
        if (m_initialized)
        {
            spdlog::warn("Engine::Init() called, but engine is already initialized.");
            return true;
        }

        spdlog::info(
            "Engine::Init() starting for backend {}",
            GraphicsBackendString(m_graphicsBackend)
        );

        try
        {
            CreateRenderer();
            if (!m_renderer)
            {
                spdlog::error("Engine::Init() failed: renderer creation returned nullptr.");
                return false;
            }
        }
        catch (const std::exception& ex)
        {
            spdlog::error("Exception during Engine::Init(): {}", ex.what());
            try
            {
                DestroyRenderer();
            }
            catch (...)
            {
                spdlog::error("Exception during cleanup in Engine::Init().");
            }
            return false;
        }
        catch (...)
        {
            spdlog::error("Unknown exception during Engine::Init().");
            try
            {
                DestroyRenderer();
            }
            catch (...)
            {
                spdlog::error("Exception during cleanup in Engine::Init() after unknown error.");
            }
            return false;
        }

        m_initialized = true;
        spdlog::info("Engine::Init() succeeded.");
        return true;
    }

    void Engine::DeInit()
    {
        if (!m_initialized)
        {
            spdlog::warn("Engine::DeInit() called but engine is not initialized.");
            return;
        }

        spdlog::info("Engine::DeInit() starting.");

        try
        {
            DestroyRenderer();
        }
        catch (const std::exception& ex)
        {
            spdlog::error("Exception in Engine::DeInit() while destroying renderer: {}", ex.what());
        }
        catch (...)
        {
            spdlog::error("Unknown exception in Engine::DeInit() while destroying renderer.");
        }

        m_initialized = false;
        spdlog::info("Engine::DeInit() finished. Engine is now deinitialized.");
    }

    void Engine::OnEvent(IEvent& event)
    {

    }

    void Engine::CreateRenderer()
    {
        spdlog::info(
            "Engine::CreateRenderer() for backend {}",
            GraphicsBackendString(m_graphicsBackend)
        );

        try
        {
            switch (m_graphicsBackend)
            {
            case GraphicsBackend::OpenGL:
                m_renderer = std::make_unique<Rendering::RendererOpenGL>();
                spdlog::info("Engine::CreateRenderer() created OpenGL renderer.");
                break;

            case GraphicsBackend::Vulkan:
                spdlog::warn("Engine::CreateRenderer(): Vulkan backend not implemented yet.");
                m_renderer.reset();
                break;

            case GraphicsBackend::None:
            default:
                spdlog::error("Engine::CreateRenderer(): Unknown graphics backend {}.",
                    GraphicsBackendString(m_graphicsBackend));
                m_renderer.reset();
                break;
            }
        }
        catch (const std::exception& ex)
        {
            spdlog::error("Exception in Engine::CreateRenderer(): {}", ex.what());
            m_renderer.reset();
        }
        catch (...)
        {
            spdlog::error("Unknown exception in Engine::CreateRenderer().");
            m_renderer.reset();
        }
    }

    void Engine::DestroyRenderer()
    {
        if (!m_renderer)
        {
            spdlog::warn("Engine::DestroyRenderer() called but renderer is already nullptr.");
            return;
        }

        spdlog::info("Engine::DestroyRenderer() starting.");

        try
        {
            m_renderer->DeInit();
        }
        catch (const std::exception& ex)
        {
            spdlog::error("Exception in Engine::DestroyRenderer() during renderer->DeInit(): {}", ex.what());
        }
        catch (...)
        {
            spdlog::error("Unknown exception in Engine::DestroyRenderer() during renderer->DeInit().");
        }

        m_renderer.reset();
        spdlog::info("Engine::DestroyRenderer() finished, renderer reset to nullptr.");
    }
}


namespace Andromeda
{
    std::unique_ptr<IEngine> CreateEngine(const GraphicsBackend& graphicsBackend)
    {
        spdlog::info(
            "CreateEngine() called with backend {}",
            GraphicsBackendString(graphicsBackend)
        );

        try
        {
            std::unique_ptr<IEngine> engine = std::make_unique<EngineCore::Engine>(graphicsBackend);
            return engine;
        }
        catch (const std::exception& ex)
        {
            spdlog::error("Exception in CreateEngine(): {}", ex.what());
        }
        catch (...)
        {
            spdlog::error("Unknown exception in CreateEngine().");
        }

        return nullptr;
    }
}
