#ifndef ENGINECORE__ENGINE__HPP
#define ENGINECORE__ENGINE__HPP

#include "../../MacroExports/include/MacroExports.hpp"
#include "Andromeda/Components/GraphicsBackend.hpp"
#include "Andromeda/Engine/IEngine.hpp"

#include "pch.hpp"


namespace Andromeda::EngineCore
{
    class ENGINECORE_API Engine : public IEngine
    {
    public:
        Engine(const GraphicsBackend& graphicsBackend);
        ~Engine() override;

        bool IsInitialized() const override;
        GraphicsBackend GetGraphicsBackend() const override;
        IRenderer* GetRenderer() const override;

        bool Init() override;
        void DeInit() override;

        void OnEvent(IEvent& event) override;

        // New: engine needs scene access to reach active camera
        void SetScene(IScene* pScene);

    private:
        void CreateRenderer();
        void DestroyRenderer();

        void HandleMouseScrolled(IEvent& event);
        void HandleMouseButtonPressed(IEvent& event);
        void HandleMouseButtonReleased(IEvent& event);
        void HandleKeyPressed(IEvent& event);
        void HandleKeyReleased(IEvent& event);
        void HandleMouseMoved(IEvent& event);

    private:
        bool m_initialized;
        GraphicsBackend m_graphicsBackend;
        std::unique_ptr<IRenderer> m_renderer;

        IScene* m_pScene;

        // Input state
        bool m_isLeftMouseDown;
        bool m_isCtrlDown;
        bool m_hasLastMousePos;
        float m_lastMouseX;
        float m_lastMouseY;

        // Tunables
        float m_mouseYawSensitivity;
        float m_mousePitchSensitivity;
        float m_mouseRollSensitivity;
        float m_scrollZoomSensitivity;
    };
}

#endif // ENGINECORE__ENGINE__HPP
