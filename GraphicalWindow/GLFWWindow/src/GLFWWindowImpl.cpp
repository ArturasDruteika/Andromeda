#include "GLFWWindowImpl.hpp"
#include "spdlog/spdlog.h"


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
				SetCallbackFunctions();
				m_isInitialized = true;
			}
		}

		void GLFWWindow::GLFWWindowImpl::DeInit()
		{
			// Cleanup
			glfwDestroyWindow(m_window);
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
			// TODO: Implement callbacks
		}

}
}