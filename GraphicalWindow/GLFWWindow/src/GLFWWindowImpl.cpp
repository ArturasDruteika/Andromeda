#include "../include/GLFWWindowImpl.hpp"


namespace Andromeda
{
	namespace GraphicalWindow
	{
		GLFWWindow::GLFWWindowImpl::GLFWWindowImpl(GLFWWindow& parent, int width, int height, const std::string& windowName, bool initWindow)
			: m_parent(parent)
			, m_width(width)
			, m_height(height)
			, m_windowName(windowName)
			, m_window(nullptr)
			, m_isInitialized(false)
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

				// Make the context current
				glfwMakeContextCurrent(m_window);

				// Initialize GLAD with modern interface
				if (!gladLoadGL(glfwGetProcAddress))
				{
					spdlog::error("Failed to initialize GLAD");
					glfwDestroyWindow(m_window);
					glfwTerminate();
					return;
				}

				const char* version = reinterpret_cast<const char*>(glGetString(GL_VERSION));
				spdlog::info("GLAD initialized successfully. OpenGL version: {}", std::string(version));

				SetCallbackFunctions();
				m_isInitialized = true;
			}
		}

		void GLFWWindow::GLFWWindowImpl::DeInit()
		{
			// Cleanup
			if (m_window)
			{
				glfwDestroyWindow(m_window);
				m_window = nullptr;
			}
			glfwTerminate();
			m_isInitialized = false;
		}

		void GLFWWindow::GLFWWindowImpl::RunMainLoop()
		{
			// Main loop
			while (!glfwWindowShouldClose(m_window))
			{
				// Clear the screen
				glClear(GL_COLOR_BUFFER_BIT);

				// Swap buffers and poll events
				glfwSwapBuffers(m_window);
				glfwPollEvents();
			}
		}

		int GLFWWindow::GLFWWindowImpl::GetWidth() const
		{
			return m_width;
		}

		int GLFWWindow::GLFWWindowImpl::GetHeight() const
		{
			return m_height;
		}

		std::string GLFWWindow::GLFWWindowImpl::GetWindowName() const
		{
			return m_windowName;
		}

		void GLFWWindow::GLFWWindowImpl::InitGLFW()
		{
			// Initialize GLFW
			if (!glfwInit())
			{
				spdlog::error("Failed to initialize GLFW");
				return;
			}
		}

		void GLFWWindow::GLFWWindowImpl::SetGLFWWindowHints()
		{
			// Set GLFW window hints
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Request OpenGL 3.3
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required on macOS
#endif
		}

		void GLFWWindow::GLFWWindowImpl::CreateWindow()
		{
			m_window = glfwCreateWindow(m_width, m_height, m_windowName.c_str(), NULL, NULL);

			if (!m_window)
			{
				spdlog::error("Failed to create GLFW window");
				glfwTerminate();
				return;
			}
		}

		void GLFWWindow::GLFWWindowImpl::SetCallbackFunctions()
		{
			// Set the resize callback
			glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
				{
					glViewport(0, 0, width, height);
					spdlog::info("Window resized to {}x{}", width, height);
				});

			// Set the mouse callback
			glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xpos, double ypos)
				{
					spdlog::info("Mouse moved to position: ({}, {})", xpos, ypos);
				});

			// Set the keyboard callback
			glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
				{
					if (action == GLFW_PRESS)
					{
						spdlog::info("Key {} pressed", key);
					}
					else if (action == GLFW_RELEASE)
					{
						spdlog::info("Key {} released", key);
					}
				});
		}
	}
}
