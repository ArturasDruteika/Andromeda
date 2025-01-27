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
			, m_imGuiManager{ nullptr }
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
                    m_context = new Context::GLFWContext();
                    m_context->Init();

                    if (m_context->IsInitialized())
                    {
                        m_window = new Window::GLFWWindow();
                        m_context->MakeContextCurrent(m_window->GetWindow());
                        InitGLAD();
                        m_window->SetCallbackFunctions();
                        m_imGuiManager = new ImGuiManager(m_window->GetWindow());
                        m_imGuiManager->Init(m_window->GetWindow());

                        // Create and initialize the Renderer
                        m_renderer = new Rendering::OpenGLRenderer();
						m_renderer->Init(m_window->GetWidth(), m_window->GetHeight());
                        m_scene = new Rendering::OpenGLScene();

                        std::vector<float> vertices = {
                            // Positions        // Colors
                            0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // Top vertex (red)
                           -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // Bottom left (green)
                            0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f  // Bottom right (blue)
                        };

                        Rendering::OpenGLRenderableObject* object = new Rendering::OpenGLRenderableObject(vertices);
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

		void Application::ApplicationImpl::RunMainLoop()
		{
            static int width{}, height{};
			while (!glfwWindowShouldClose(m_window->GetWindow()))
			{
                glfwPollEvents();
				width = m_window->GetWidth();
				height = m_window->GetHeight();
                m_renderer->RenderFrame(*m_scene, width, height);
                m_imGuiManager->Render(m_renderer->GetFrameBufferObjectTexture(), width, height);
				glfwSwapBuffers(m_window->GetWindow());
			}
		}

        void Application::ApplicationImpl::DeInit()
        {
			if (m_isInitialized)
			{
                m_imGuiManager->DeInit();
                delete m_imGuiManager;
                m_imGuiManager = nullptr;
				m_renderer->DeInit();
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

        void Application::ApplicationImpl::InitGLAD()
        {
            if (!gladLoadGL(glfwGetProcAddress))
            {
                spdlog::error("Failed to initialize GLAD.");
                return;
            }
            const char* version = reinterpret_cast<const char*>(glGetString(GL_VERSION));
            spdlog::info("GLAD initialized successfully. OpenGL version: {}", std::string(version));
        }
	}
}