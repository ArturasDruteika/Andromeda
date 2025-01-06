#include "../include/GLFWWindowImpl.hpp"

namespace Andromeda
{
    namespace EngineCore
    {
        GLFWWindow::GLFWWindowImpl::GLFWWindowImpl(GLFWWindow& parent, int width, int height, const std::string& windowName, bool initWindow)
			: m_parent{ parent }
			, m_width{ width }
			, m_height{ height }
			, m_windowName{ windowName }
			, m_window{ nullptr }
			, m_isInitialized{ false }
			, m_renderer{ nullptr }
            , m_context{ nullptr }
        {
            if (initWindow)
            {
                Init();
            }
        }

        GLFWWindow::GLFWWindowImpl::~GLFWWindowImpl()
        {
            DeInit();
        }

        void GLFWWindow::GLFWWindowImpl::Init()
        {
            if (!m_isInitialized)
            {
                m_context = new GLFWContext();
                m_context->InitGLFW();
                if (m_context->IsInitialized())
                {
                    CreateWindow();
                    m_context->MakeContextCurrent(m_window);
                    m_context->LoadGLAD();
                    m_context->SetContextHints();

                    // Create and initialize the Renderer
                    m_renderer = new Renderer::OpenGLRenderer();
                    m_renderer->Initialize();

                    SetCallbackFunctions();
                    m_isInitialized = true;
                }
            }
        }

        void GLFWWindow::GLFWWindowImpl::RunMainLoop()
        {
            while (!glfwWindowShouldClose(m_window))
            {
                // Delegate rendering to the Renderer
                m_renderer->RenderFrame();

                // Swap buffers and poll events
                glfwSwapBuffers(m_window);
                glfwPollEvents();
            }
        }

        unsigned int GLFWWindow::GLFWWindowImpl::GetWidth() const
        {
            return m_width;
        }

        unsigned int GLFWWindow::GLFWWindowImpl::GetHeight() const
        {
            return m_height;
        }

        std::string GLFWWindow::GLFWWindowImpl::GetWindowName() const
        {
            return m_windowName;
        }

        bool GLFWWindow::GLFWWindowImpl::IsInitialized()
        {
            return m_isInitialized;
        }

        void GLFWWindow::GLFWWindowImpl::DeInit()
        {
            if (m_renderer)
            {
                m_renderer->Shutdown();
				delete m_renderer;
            }
            if (m_window)
            {
                glfwDestroyWindow(m_window);
                m_window = nullptr;
            }
            if (m_context->IsInitialized())
            {
                m_context->TerminateGLFW();
            }

            m_isInitialized = false;
        }

        void GLFWWindow::GLFWWindowImpl::CreateWindow()
        {
            m_window = glfwCreateWindow(m_width, m_height, m_windowName.c_str(), nullptr, nullptr);

            if (!m_window)
            {
                spdlog::error("Failed to create GLFW window.");
                glfwTerminate();
            }
        }

        void GLFWWindow::GLFWWindowImpl::SetCallbackFunctions()
        {
            glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
                {
                    glViewport(0, 0, width, height);
                    spdlog::info("Window resized to {}x{}", width, height);
                });
        }
    }
}
