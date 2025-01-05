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
                InitGLFW();
                SetGLFWWindowHints();
                CreateWindow();
				GLFWMakeContextCurrent();
				LoadGLAD();

                // Create and initialize the Renderer
                m_renderer = new Renderer::OpenGLRenderer();
                m_renderer->Initialize();

                SetCallbackFunctions();
                m_isInitialized = true;
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

            glfwTerminate();
            m_isInitialized = false;
        }

        void GLFWWindow::GLFWWindowImpl::InitGLFW()
        {
            if (!glfwInit())
            {
                spdlog::error("Failed to initialize GLFW.");
            }
        }

        void GLFWWindow::GLFWWindowImpl::SetGLFWWindowHints()
        {
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required on macOS
#endif
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

        void GLFWWindow::GLFWWindowImpl::GLFWMakeContextCurrent()
        {
            // Make the OpenGL context current
            glfwMakeContextCurrent(m_window);

            if (glfwGetCurrentContext() == nullptr)
            {
                spdlog::error("Failed to make OpenGL context current.");
                glfwDestroyWindow(m_window);
                glfwTerminate();
                return;
            }
        }

        void GLFWWindow::GLFWWindowImpl::LoadGLAD()
        {
            if (!gladLoadGL(glfwGetProcAddress))
            {
                spdlog::error("Failed to initialize GLAD.");
                glfwDestroyWindow(m_window);
                glfwTerminate();
                return;
            }

            const char* version = reinterpret_cast<const char*>(glGetString(GL_VERSION));
            spdlog::info("GLAD initialized successfully. OpenGL version: {}", std::string(version));
        }
    }
}
