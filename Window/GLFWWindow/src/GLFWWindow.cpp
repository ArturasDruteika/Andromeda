#include "../include/GLFWWindow.hpp"


namespace Andromeda
{
	namespace Window
	{
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

		void GLFWWindow::DeInit()
		{
			if (m_isInitialized)
			{
				glfwDestroyWindow(m_window);
				m_isInitialized = false;
			}
		}

		void GLFWWindow::CreateWindow()
		{
			m_window = glfwCreateWindow(m_width, m_height, m_windowName.c_str(), nullptr, nullptr);

			if (!m_window)
			{
				spdlog::error("Failed to create GLFW window.");
				return;
			}

			// Associate this instance with the GLFW window
			glfwSetWindowUserPointer(m_window, this);
		}

		void GLFWWindow::SetCallbackFunctions()
		{
			glfwSetFramebufferSizeCallback(m_window, ResizeWindow);
			glfwSetWindowCloseCallback(m_window, WindowClose);
			glfwSetKeyCallback(m_window, KeyCallback);
			glfwSetMouseButtonCallback(m_window, MouseButtonCallback);
			glfwSetScrollCallback(m_window, MouseScrollCallback);
			glfwSetCursorPosCallback(m_window, MouseMoveCallback);
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

		void GLFWWindow::SetEventCallback(const EventCallbackFn& callback)
		{
			m_EventCallback = callback;
		}

		void GLFWWindow::ResizeWindow(GLFWwindow* window, int width, int height)
		{
			GLFWWindow* instance = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
			if (instance)
			{
				instance->m_width = width;
				instance->m_height = height;
				// spdlog::debug("Window resized to {}x{}", width, height);

				if (instance->m_EventCallback)
				{
					WindowResizeEvent event(width, height);
					instance->m_EventCallback(event);
				}
			}
		}

		void GLFWWindow::WindowClose(GLFWwindow* window)
		{
			GLFWWindow* instance = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
			if (instance)
			{
				// spdlog::debug("Window close event triggered.");
				if (instance->m_EventCallback)
				{
					WindowCloseEvent event;
					instance->m_EventCallback(event);
				}
			}
		}

		void GLFWWindow::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			GLFWWindow* instance = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
			if (instance)
			{
				if (instance->m_EventCallback)
				{
					if (action == GLFW_PRESS || action == GLFW_REPEAT)
					{
						KeyPressedEvent event(static_cast<KeyCode>(key), action == GLFW_REPEAT);
						// spdlog::debug("Key Pressed: {} (Repeat: {})", key, action == GLFW_REPEAT);
						instance->m_EventCallback(event);
					}
					else if (action == GLFW_RELEASE)
					{
						KeyReleasedEvent event(static_cast<KeyCode>(key));
						// spdlog::debug("Key Released: {}", key);
						instance->m_EventCallback(event);
					}
				}
			}
		}

		void GLFWWindow::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
		{
			GLFWWindow* instance = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
			if (instance)
			{
				if (instance->m_EventCallback)
				{
					if (action == GLFW_PRESS)
					{
						MouseButtonPressedEvent event(static_cast<MouseCode>(button));
						// spdlog::debug("Mouse Button Pressed: {}", button);
						instance->m_EventCallback(event);
					}
					else if (action == GLFW_RELEASE)
					{
						MouseButtonReleasedEvent event(static_cast<MouseCode>(button));
						// spdlog::debug("Mouse Button Released: {}", button);
						instance->m_EventCallback(event);
					}
				}
			}
		}

		void GLFWWindow::MouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
		{
			GLFWWindow* instance = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
			if (instance)
			{
				if (instance->m_EventCallback)
				{
					MouseScrolledEvent event(static_cast<float>(xOffset), static_cast<float>(yOffset));
					// spdlog::debug("Mouse Scrolled: X Offset = {}, Y Offset = {}", xOffset, yOffset);
					instance->m_EventCallback(event);
				}
			}
		}

		void GLFWWindow::MouseMoveCallback(GLFWwindow* window, double xPos, double yPos)
		{
			GLFWWindow* instance = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
			if (instance)
			{
				if (instance->m_EventCallback)
				{
					MouseMovedEvent event(static_cast<float>(xPos), static_cast<float>(yPos));
					// spdlog::debug("Mouse Moved: X = {}, Y = {}", xPos, yPos);
					instance->m_EventCallback(event);
				}
			}
		}

	}
}
