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

        bool GLFWWindow::IsInitialized() const
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
            glfwSetFramebufferSizeCallback(m_window, ResizeWindow);
        }

        void GLFWWindow::CreateWindow()
        {
            m_window = glfwCreateWindow(m_width, m_height, m_windowName.c_str(), nullptr, nullptr);

            if (!m_window)
            {
                spdlog::error("Failed to create GLFW window.");
            }

            // Associate this instance with the GLFW window
            glfwSetWindowUserPointer(m_window, this);
        }

        void GLFWWindow::ResizeWindow(GLFWwindow* window, int width, int height)
        {
            // Retrieve the instance of GLFWWindow associated with this GLFWwindow
            GLFWWindow* instance = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
            if (instance)
            {
                instance->m_width = width;  // Update the instance's width
                instance->m_height = height; // Update the instance's height
                spdlog::info("Window resized to {}x{}", width, height);

                // Emit the signal for other listeners
                OnResizeWindow(width, height);
            }

            // Update OpenGL viewport as well
            glViewport(0, 0, width, height);
        }
	}
}