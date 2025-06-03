#include "../include/ApplicationImpl.hpp"
#include "VertexLayouts.hpp"
#include "VertexAttributes.hpp"
#include "Vertex.hpp"
#include "Points.hpp"
#include "Colors.hpp"
#include "Constants.hpp"


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
			, m_pRendererWindowOpenGL{ nullptr }
			, m_pCamera{ nullptr }
            , m_LastMouseDragPos{ -1.0f, -1.0f }
            , m_pCameraInputMapper{ nullptr }
			, m_pImGuiDockspaceManager{ nullptr }
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
						m_pImGuiDockspaceManager = new ImGuiDockspaceManager(m_pWindow->GetWindow());
                        m_pRendererWindowOpenGL = new RendererWindowOpenGL(0, "Renderer Window OpenGL");
						m_pImGuiDockspaceManager->AddGraphicalModalWindow(m_pRendererWindowOpenGL->GetID(), m_pRendererWindowOpenGL);
                        m_pCamera = new Rendering::Camera();
                        m_pCameraInputMapper = new CameraInputMapper(m_pCamera);

                        // Call the function to set up event callbacks
                        SetupEventCallbacks();

                        // Create and initialize the Renderer
                        m_pRenderer = new Rendering::OpenGLRenderer();
                        m_pRenderer->Init(m_pWindow->GetWidth(), m_pWindow->GetHeight());
                        m_pScene = new Rendering::OpenGLScene();

						m_pRenderer->SetCamera(m_pCamera);

						SetupImGuiCallbacks();
                       
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
                m_pRendererWindowOpenGL->SetTextureID(m_pRenderer->GetFrameBufferObjectTexture());
                m_pImGuiDockspaceManager->Render();
				glfwSwapBuffers(m_pWindow->GetWindow());
			}
		}

        void Application::ApplicationImpl::DeInit()
        {
			if (m_isInitialized)
			{
				m_pRenderer->DeInit();
				delete m_pRenderer;
				m_pRenderer = nullptr;
				delete m_pScene;
				m_pScene = nullptr;
				m_pContext->TerminateGLFW();
				delete m_pContext;
				m_pContext = nullptr;
				m_isInitialized = false;
                delete m_pCamera;
				m_pCamera = nullptr;
				delete m_pCameraInputMapper;
				m_pCameraInputMapper = nullptr;
				delete m_pImGuiDockspaceManager;
				m_pImGuiDockspaceManager = nullptr;
			}
        }

        void Application::ApplicationImpl::AddToScene(int id, Rendering::IRenderableObjectOpenGL* object)
        {
			m_pScene->AddObject(id, object);
        }

        void Application::ApplicationImpl::RemoveFromScene(int id)
        {
            m_pScene->RemoveObject(id);
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

            m_pWindow->SetEventCallback(EventCallback);
        }

        void Application::ApplicationImpl::SetupImGuiCallbacks()
        {
            m_pRendererWindowOpenGL->SetOnResizeCallback(
                std::bind(
                    &Rendering::OpenGLRenderer::Resize, 
                    m_pRenderer, 
                    std::placeholders::_1, 
                    std::placeholders::_2
                )
            );

			m_pRendererWindowOpenGL->SetOnMouseMoveCallback(
				std::bind(
					&Application::ApplicationImpl::OnMouseDragged,
					this,
					std::placeholders::_1,
					std::placeholders::_2,
                    std::placeholders::_3
				)
			);

			m_pRendererWindowOpenGL->SetOnMouseScrollCallback(
				std::bind(
					&Application::ApplicationImpl::OnMouseScroll,
					this,
					std::placeholders::_1
				)
			);

            m_pCamera->SetOnDistanceChange(
                std::bind(
                    &Rendering::OpenGLScene::ResizeGrid,
                    m_pScene,
                    std::placeholders::_1
                )
            );
        }

		// TODO: Conside moving this to a separate or Camera class
        void Application::ApplicationImpl::OnMouseDragged(float x, float y, bool ctrlHeld)
        {
            if (m_LastMouseDragPos[0] < 0.0f || m_LastMouseDragPos[1] < 0.0f)
            {
                // First drag event
                m_LastMouseDragPos = { x, y };
                return;
            }
            m_pCameraInputMapper->MouseMovementToRotation(x, y, ctrlHeld);
        }

        void Application::ApplicationImpl::OnMouseScroll(float scrollY)
        {
			m_pCameraInputMapper->MouseScrollToZoom(scrollY);
        }

        void Application::ApplicationImpl::EventCallback(Window::Event& event)
        {
            Window::EventDispatcher dispatcher(event);
        }
	}
}
