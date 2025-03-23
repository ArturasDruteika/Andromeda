#include "../include/ApplicationImpl.hpp"
#include "VertexLayouts.hpp"
#include "VertexAttributes.hpp"
#include "Vertex.hpp"
#include "Points.hpp"
#include "Colors.hpp"

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
#if !defined(NDEBUG) || defined(_DEBUG)
            // Enable debug logging
            spdlog::set_level(spdlog::level::debug);
#endif

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

                        // 🔹 Call the function to set up event callbacks
                        SetupEventCallbacks();

                        // Create and initialize the Renderer
                        m_pRenderer = new Rendering::OpenGLRenderer();
                        m_pRenderer->Init(m_pWindow->GetWidth(), m_pWindow->GetHeight());
                        m_pScene = new Rendering::OpenGLScene();

						SetupImGuiCallbacks();
                        
                        std::vector<Rendering::Vertex> vertices = {
							{ Rendering::Point3D{ -0.5f,  0.5f, 0.0f }, Rendering::Color{ 1.0f, 0.0f, 0.0f, 1.0f} }, // Top Left
							{ Rendering::Point3D{ 0.5f,  0.5f, 0.0f }, Rendering::Color{ 0.0f, 1.0f, 0.0f, 1.0f} }, // Top Right
							{ Rendering::Point3D{ 0.5f, -0.5f, 0.0f }, Rendering::Color{ 0.0f, 0.0f, 1.0f, 1.0f} }, // Bottom Right
							{ Rendering::Point3D{ -0.5f, -0.5f, 0.0f }, Rendering::Color{ 1.0f, 1.0f, 0.0f, 1.0f} } // Bottom Left
                        };

                        std::vector<unsigned int> indices = {
                            0, 1, 2, // First triangle
                            2, 3, 0  // Second triangle
                        };

                        Rendering::VertexLayout vertexLayout = std::vector{
                            Rendering::VertexAttributes{ 0, Rendering::Point3D::Size(), GL_FLOAT, GL_FALSE, sizeof(Rendering::Vertex), 0}, // Position
                            Rendering::VertexAttributes{ 1, Rendering::Color::Size(), GL_FLOAT, GL_FALSE, sizeof(Rendering::Vertex), sizeof(Rendering::Point3D)} // Color
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

        void Application::ApplicationImpl::SetupEventCallbacks()
        {
            if (!m_pWindow) return;

            // 🔹 Pass a function pointer instead of a lambda
            m_pWindow->SetEventCallback(EventCallback);
        }

        void Application::ApplicationImpl::SetupImGuiCallbacks()
        {
            m_pImGuiManager->SetOnResizeCallback(
                std::bind(
                    &Rendering::OpenGLRenderer::Resize, 
                    m_pRenderer, 
                    std::placeholders::_1, 
                    std::placeholders::_2
                )
            );
        }

        void Application::ApplicationImpl::EventCallback(Window::Event& event)
        {
            spdlog::debug("Event received: {}", event.ToString());

            Window::EventDispatcher dispatcher(event);
        }
	}
}
