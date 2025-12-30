#include "../include/Engine.hpp"
#include "Rendering/Renderers/Renderers/include/RendererOpenGL.hpp"
#include "Andromeda/Window/Events/EventType.hpp"
#include "Andromeda/Window/MouseAndKeyCodes/MouseCodes.hpp"
#include "Andromeda/Window/MouseAndKeyCodes/KeyCodes.hpp"
#include "Andromeda/Window/Events/IKeyEvents.hpp"
#include "Andromeda/Window/Events/IMouseEvents.hpp"
#include "Andromeda/Space/Camera/ICameraController.hpp"

#include "spdlog/spdlog.h"


namespace Andromeda::EngineCore
{
    static constexpr float DEFAULT_MOUSE_YAW_SENSITIVITY = 0.005f;
    static constexpr float DEFAULT_MOUSE_PITCH_SENSITIVITY = 0.005f;
    static constexpr float DEFAULT_MOUSE_ROLL_SENSITIVITY = 0.005f;
    static constexpr float DEFAULT_SCROLL_ZOOM_SENSITIVITY = 0.25f;

    Engine::Engine(const GraphicsBackend& graphicsBackend)
        : m_initialized{ false }
        , m_graphicsBackend{ graphicsBackend }
        , m_renderer{ nullptr }
        , m_pScene{ nullptr }
        , m_isLeftMouseDown{ false }
        , m_isCtrlDown{ false }
        , m_hasLastMousePos{ false }
        , m_lastMouseX{ 0.0f }
        , m_lastMouseY{ 0.0f }
        , m_mouseYawSensitivity{ DEFAULT_MOUSE_YAW_SENSITIVITY }
        , m_mousePitchSensitivity{ DEFAULT_MOUSE_PITCH_SENSITIVITY }
        , m_mouseRollSensitivity{ DEFAULT_MOUSE_ROLL_SENSITIVITY }
        , m_scrollZoomSensitivity{ DEFAULT_SCROLL_ZOOM_SENSITIVITY }
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

    void Engine::SetScene(IScene* pScene)
    {
        m_pScene = pScene;
    }

    static ICameraController* GetActiveCameraControllerFromScene(IScene* pScene)
    {
        if (!pScene)
        {
            return nullptr;
        }

        // Assumption: IScene::GetActiveCamera() exists and returns an ICamera* (or something base).
        // If your actual API differs, adjust this part.
        ICamera* pCameraBase = pScene->GetActiveCamera();
        if (!pCameraBase)
        {
            return nullptr;
        }

        // We need Rotate/Zoom, so cast to ICameraController.
        return dynamic_cast<ICameraController*>(pCameraBase);
    }

    void Engine::OnEvent(IEvent& event)
    {
        switch (event.GetEventType())
        {
            case EventType::MouseScrolled:
            {
                HandleMouseScrolled(event);
                break;
            }

            case EventType::MouseButtonPressed:
            {
                HandleMouseButtonPressed(event);
                break;
            }

            case EventType::MouseButtonReleased:
            {
                HandleMouseButtonReleased(event);
                break;
            }

            case EventType::KeyPressed:
            {
                HandleKeyPressed(event);
                break;
            }

            case EventType::KeyReleased:
            {
                HandleKeyReleased(event);
                break;
            }

            case EventType::MouseMoved:
            {
                HandleMouseMoved(event);
                break;
            }

            default:
            {
                break;
            }
        }
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
            {
                m_renderer = std::make_unique<Rendering::RendererOpenGL>();
                spdlog::info("Engine::CreateRenderer() created OpenGL renderer.");
                break;
            }

            case GraphicsBackend::Vulkan:
            {
                spdlog::warn("Engine::CreateRenderer(): Vulkan backend not implemented yet.");
                m_renderer.reset();
                break;
            }

            case GraphicsBackend::None:
            default:
            {
                spdlog::error(
                    "Engine::CreateRenderer(): Unknown graphics backend {}.",
                    GraphicsBackendString(m_graphicsBackend)
                );
                m_renderer.reset();
                break;
            }
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

    void Engine::HandleMouseScrolled(IEvent& event)
    {
        IMouseScrolledEvent* e = dynamic_cast<IMouseScrolledEvent*>(&event);
        if (!e)
        {
            return;
        }

        ICameraController* pCamera = GetActiveCameraControllerFromScene(m_pScene);
        if (!pCamera)
        {
            return;
        }

        const float zoomDelta = -e->GetYOffset() * m_scrollZoomSensitivity;
        pCamera->Zoom(zoomDelta);
    }

    void Engine::HandleMouseButtonPressed(IEvent& event)
    {
        IMouseButtonPressedEvent* e = dynamic_cast<IMouseButtonPressedEvent*>(&event);
        if (!e)
        {
            return;
        }

        if (e->GetMouseButton() == ButtonLeft)
        {
            m_isLeftMouseDown = true;
            m_hasLastMousePos = false;
        }
    }

    void Engine::HandleMouseButtonReleased(IEvent& event)
    {
        IMouseButtonReleasedEvent* e = dynamic_cast<IMouseButtonReleasedEvent*>(&event);
        if (!e)
        {
            return;
        }

        if (e->GetMouseButton() == ButtonLeft)
        {
            m_isLeftMouseDown = false;
            m_hasLastMousePos = false;
        }
    }

    void Engine::HandleKeyPressed(IEvent& event)
    {
        IKeyPressedEvent* e = dynamic_cast<IKeyPressedEvent*>(&event);
        if (!e)
        {
            return;
        }

        const KeyCode key = e->GetKeyCode();
        if (key == LeftControl || key == RightControl)
        {
            m_isCtrlDown = true;
        }
    }

    void Engine::HandleKeyReleased(IEvent& event)
    {
        IKeyReleasedEvent* e = dynamic_cast<IKeyReleasedEvent*>(&event);
        if (!e)
        {
            return;
        }

        const KeyCode key = e->GetKeyCode();
        if (key == LeftControl || key == RightControl)
        {
            m_isCtrlDown = false;
        }
    }

    void Engine::HandleMouseMoved(IEvent& event)
    {
        IMouseMovedEvent* e = dynamic_cast<IMouseMovedEvent*>(&event);
        if (!e)
        {
            return;
        }

        ICameraController* pCamera = GetActiveCameraControllerFromScene(m_pScene);
        if (!pCamera)
        {
            return;
        }

        const float x = e->GetX();
        const float y = e->GetY();

        if (!m_isLeftMouseDown)
        {
            m_lastMouseX = x;
            m_lastMouseY = y;
            m_hasLastMousePos = true;
            return;
        }

        if (!m_hasLastMousePos)
        {
            m_lastMouseX = x;
            m_lastMouseY = y;
            m_hasLastMousePos = true;
            return;
        }

        const float dx = x - m_lastMouseX;
        const float dy = y - m_lastMouseY;

        m_lastMouseX = x;
        m_lastMouseY = y;

        if (m_isCtrlDown)
        {
            const float roll = dx * m_mouseRollSensitivity;
            pCamera->Rotate(0.0f, 0.0f, roll);
        }
        else
        {
            const float yaw = dx * m_mouseYawSensitivity;
            const float pitch = dy * m_mousePitchSensitivity;
            pCamera->Rotate(yaw, pitch, 0.0f);
        }
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
