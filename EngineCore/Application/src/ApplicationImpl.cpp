#include "../include/ApplicationImpl.hpp"


namespace Andromeda
{
	namespace EngineCore
	{
		Application::ApplicationImpl::ApplicationImpl()
            : m_isInitialized{ false }
			, m_context{ nullptr }
			, m_window{ nullptr }
			, m_renderer{ nullptr }
			, m_scene{ nullptr }
		{
		}

		Application::ApplicationImpl::~ApplicationImpl() = default;

		void Application::ApplicationImpl::RunMainLoop()
		{
            while (!glfwWindowShouldClose(m_window->GetWindow()))
            {
                m_renderer->RenderFrame(*m_scene);
                glfwSwapBuffers(m_window->GetWindow());
                glfwPollEvents();
            }
		}

		void Application::ApplicationImpl::Init()
		{
            if (!m_isInitialized)
            {
                try
                {
                    InitGLFW();
                    m_context = new Context::GLFWContext();
                    m_context->InitGLFW();

                    if (m_context->IsInitialized())
                    {
                        m_window = new Window::GLFWWindow();
                        m_context->MakeContextCurrent(m_window->GetWindow());
                        m_window->SetCallbackFunctions();

                        // Create and initialize the Renderer
                        m_renderer = new Renderer::OpenGLRenderer();
                        m_scene = new Environment::OpenGLScene();
                        m_renderer->Initialize(reinterpret_cast<const char*>(m_context->GetGLFWglproc()));

                        std::vector<float> vertices = {
                            // Positions        // Colors
                            0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // Top vertex (red)
                           -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // Bottom left (green)
                            0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f  // Bottom right (blue)
                        };

                        Environment::OpenGLRenderableObject* object = new Environment::OpenGLRenderableObject(vertices);
                        // TODO: implement dynamic ID assignment
                        m_scene->AddObject(0, object);
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

        void Application::ApplicationImpl::DeInit()
        {
			if (m_isInitialized)
			{
				m_renderer->Shutdown();
				delete m_renderer;
				m_renderer = nullptr;
				delete m_scene;
				m_scene = nullptr;
				m_context->TerminateGLFW();
				delete m_context;
				m_context = nullptr;
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