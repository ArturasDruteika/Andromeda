#include "../include/GLFWWindow.hpp"


namespace Andromeda
{
	namespace Window
	{
        ResizeWindowSignal GLFWWindow::OnResizeWindow;

        GLFWWindow::GLFWWindow(int width, int height, const std::string& windowName, bool initWindow)
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

        GLFWWindow::~GLFWWindow()
        {
            DeInit();
        }

        void GLFWWindow::Init()
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

        unsigned int GLFWWindow::GetWidth() const
        {
            return m_width;
        }

        unsigned int GLFWWindow::GetHeight() const
        {
            return m_height;
        }

        std::string GLFWWindow::GetWindowName() const
        {
            return m_windowName;
        }

        bool GLFWWindow::IsInitialized()
        {
            return m_isInitialized;
        }

        GLFWwindow* GLFWWindow::GetWindow() const
        {
            return m_window;
        }

        void GLFWWindow::DeInit()
        {
            if (m_window)
            {
                glfwDestroyWindow(m_window);
                m_window = nullptr;
            }

            m_isInitialized = false;
        }

        void GLFWWindow::SetCallbackFunctions()
        {
            glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
                {
                    glViewport(0, 0, width, height);
                    spdlog::info("Window resized to {}x{}", width, height);
                    OnResizeWindow(width, height);
                });
        }

        void GLFWWindow::CreateWindow()
        {
            m_window = glfwCreateWindow(m_width, m_height, m_windowName.c_str(), nullptr, nullptr);

            if (!m_window)
            {
                spdlog::error("Failed to create GLFW window.");
            }
        }

        void GLFWWindow::ResizeWindow(int width, int height)
        {
            glViewport(0, 0, width, height);
            spdlog::info("Window resized to {}x{}", width, height);
        }
	}
}