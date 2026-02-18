#ifndef APPLICATION__APPLICATION__HPP
#define APPLICATION__APPLICATION__HPP


#include "Andromeda/Components/GraphicsBackend.hpp"
#include "Andromeda/Application/IApplication.hpp"
#include "Andromeda/Engine/IEngine.hpp"
#include "Andromeda/Platform/IPlatform.hpp"
#include "Andromeda/Space/Scene/IScene.hpp"
#include "pch.hpp"


namespace Andromeda::Application
{
    class Application
        : public virtual IApplication
    {
    public:
        explicit Application(GraphicsBackend graphicsBackend);
        ~Application() override;

        Application(const Application& other) = delete;
        Application& operator=(const Application& other) = delete;

        Application(Application&& other) noexcept = delete;
        Application& operator=(Application&& other) noexcept = delete;

        // Getters
        IRenderer* GetRenderer() override;

        bool Init(
            unsigned int width, 
            unsigned int height, 
            const std::string& title
        ) override;
        void DeInit() override;

        void SetScene(IScene* pScene) override;

        // Returns 0 on clean exit, non-zero on error
        int Run() override;

    private:
        bool InitPlatform(unsigned int width, unsigned int height, const std::string& title);
        bool InitEngine();
        bool InitRenderer(int width, int height);
        bool InitInternal(
            unsigned int width, 
            unsigned int height, 
            const std::string& title
        );
        void ConnectEvents();
        void RenderLoop();

    private:
        bool m_initialized;
        GraphicsBackend m_graphicsBackend;

        std::unique_ptr<IPlatform> m_pPlatform;
        std::unique_ptr<IEngine> m_pEngine;

        IScene* m_pScene;
        IWindow* m_pWindow;
        IGraphicsContext* m_pContext;
        IRenderer* m_pRenderer;
    };
}

#endif // APPLICATION__APPLICATION__HPP
