#include "../include/ApplicationImpl.hpp"
#include "VertexLayouts.hpp"
#include "VertexAttributes.hpp"


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

                        // Set the resize callback in ImGuiManager
                        m_pImGuiManager->SetOnResizeCallback(
                            [this](int newWidth, int newHeight) 
                            {
                                if (m_pRenderer)
                                {
                                    m_pRenderer->Resize(newWidth, newHeight);
                                }
                            }
                        );

                        std::vector<float> vertices = {
                            // Positions        // Colors
                           -0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // Top left (red)
                            0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // Top right (green)
                            0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f, // Bottom right (blue)
                           -0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 0.0f  // Bottom left (yellow)
                        };

                        std::vector<unsigned int> indices = {
                            0, 1, 2, // First triangle
                            2, 3, 0  // Second triangle
                        };

                        Rendering::VertexLayout vertexLayout = std::vector{
                            Rendering::VertexAttributes{ 0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0 }, // Position
                            Rendering::VertexAttributes{ 1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 3 * sizeof(float) } // Color
                        };

                        Rendering::OpenGLRenderableObject* object = new Rendering::OpenGLRenderableObject(vertices, indices, vertexLayout);
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
			while (!glfwWindowShouldClose(m_pWindow->GetWindow()))
			{
                glfwPollEvents();
                m_pRenderer->RenderFrame(*m_pScene);
                m_pImGuiManager->Render(m_pRenderer->GetFrameBufferObjectTexture());
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