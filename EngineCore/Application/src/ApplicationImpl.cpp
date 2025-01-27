#include "../include/ApplicationImpl.hpp"


namespace Andromeda
{
	namespace EngineCore
	{
		Application::ApplicationImpl::ApplicationImpl()
            : m_isInitialized{ false }
			, m_pContext{ nullptr }
			, m_pWindow{ nullptr }
			, m_pRenderer{ nullptr }
			, m_pScene{ nullptr }
			, m_pImGuiManager{ nullptr }
		{
		}

		Application::ApplicationImpl::~ApplicationImpl() = default;

        void Application::ApplicationImpl::Init()
        {
            if (!m_isInitialized)
            {
                try
                {
                    InitGLFW();
                    m_pContext = new Context::GLFWContext();
                    m_pContext->Init();

                    if (m_pContext->IsInitialized())
                    {
                        m_pWindow = new Window::GLFWWindow();
                        m_pContext->MakeContextCurrent(m_pWindow->GetWindow());
                        m_openGLLoader.LoadGlad(reinterpret_cast<const char*>(glfwGetProcAddress));
                        m_pWindow->SetCallbackFunctions();
                        m_pImGuiManager = new ImGuiManager(m_pWindow->GetWindow());
                        m_pImGuiManager->Init(m_pWindow->GetWindow());

                        // Create and initialize the Renderer
                        m_pRenderer = new Rendering::OpenGLRenderer();
						m_pRenderer->Init(m_pWindow->GetWidth(), m_pWindow->GetHeight());
                        m_pScene = new Rendering::OpenGLScene();

                        std::vector<float> vertices = {
                            // Positions        // Colors
                            0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // Top vertex (red)
                           -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // Bottom left (green)
                            0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f  // Bottom right (blue)
                        };

                        Rendering::OpenGLRenderableObject* object = new Rendering::OpenGLRenderableObject(vertices);
                        // TODO: implement dynamic ID assignment
                        m_pScene->AddObject(0, object);
                        m_isInitialized = true;
                    }
                }
                catch (const std::exception& e)
                {
                    spdlog::error("Initialization failed: {}", e.what());
                    DeInit();
                }
            }
        }

		void Application::ApplicationImpl::RunMainLoop()
		{
            static int width{}, height{};
			while (!glfwWindowShouldClose(m_pWindow->GetWindow()))
			{
                glfwPollEvents();
				width = m_pWindow->GetWidth();
				height = m_pWindow->GetHeight();
                m_pRenderer->RenderFrame(*m_pScene, width, height);
                m_pImGuiManager->Render(m_pRenderer->GetFrameBufferObjectTexture(), width, height);
				glfwSwapBuffers(m_pWindow->GetWindow());
			}
		}

        void Application::ApplicationImpl::DeInit()
        {
			if (m_isInitialized)
			{
                m_pImGuiManager->DeInit();
                delete m_pImGuiManager;
                m_pImGuiManager = nullptr;
				m_pRenderer->DeInit();
				delete m_pRenderer;
				m_pRenderer = nullptr;
				delete m_pScene;
				m_pScene = nullptr;
				m_pContext->TerminateGLFW();
				delete m_pContext;
				m_pContext = nullptr;
				m_isInitialized = false;
			}
        }

        void Application::ApplicationImpl::InitGLFW()
        {
            if (!glfwInit())
            {
                spdlog::error("Failed to initialize GLFW.");
            }
            spdlog::info("GLFW initialized successfully.");
        }
	}
}