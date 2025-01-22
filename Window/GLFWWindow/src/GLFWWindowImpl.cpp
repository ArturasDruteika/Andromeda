#include "../include/GLFWWindowImpl.hpp"


namespace Andromeda
{
    namespace Window
    {
        GLFWWindow::GLFWWindowImpl::GLFWWindowImpl(int width, int height, const std::string& windowName, bool initWindow)
			: m_width{ width }
			, m_height{ height }
			, m_windowName{ windowName }
			, m_window{ nullptr }
			, m_isInitialized{ false }
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
                try
                {
                    CreateWindow();
                    SetCallbackFunctions();
                    m_isInitialized = true;
                }
                catch (const std::exception& e)
                {
                    spdlog::error("Initialization failed: {}", e.what());
                    DeInit();
                }
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

        GLFWwindow* GLFWWindow::GLFWWindowImpl::GetWindow() const
        {
            return m_window;
        }

        void GLFWWindow::GLFWWindowImpl::DeInit()
        {
            if (m_window)
            {
                glfwDestroyWindow(m_window);
                m_window = nullptr;
            }

            m_isInitialized = false;
        }

        void GLFWWindow::GLFWWindowImpl::SetCallbackFunctions()
        {
            glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
                {
                    glViewport(0, 0, width, height);
                    spdlog::info("Window resized to {}x{}", width, height);
                });
        }

        void GLFWWindow::GLFWWindowImpl::CreateWindow()
        {
            m_window = glfwCreateWindow(m_width, m_height, m_windowName.c_str(), nullptr, nullptr);

            if (!m_window)
            {
                spdlog::error("Failed to create GLFW window.");
            }
        }
    }
}
