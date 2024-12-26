#include "Window.hpp"
#include "spdlog/spdlog.h"



namespace Andromeda
{
	namespace Window
	{
		Window::Window(int width, int height, const std::string& windowName)
			: m_width(width)
			, m_height(height)
			, m_windowName(windowName)
			, m_window(nullptr)
		{
			Init();
		}

		Window::~Window()
		{
		}

		int Window::GetWidth()
		{
			return m_width;
		}

		int Window::GetHeight()
		{
			return m_height;
		}

		std::string Window::GetWindowName()
		{
			return m_windowName;
		}

		void Window::InitGLFW()
		{
			// Initialize GLFW
			if (!glfwInit())
			{
				spdlog::error("Failed to initialize GLFW");
				return;
			}
		}

		void Window::SetGLFWWindowHints()
		{
			// Set GLFW window hints
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Request OpenGL 3.3
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required on macOS
#endif
		}

		void Window::CreateWindow()
		{
			m_window = glfwCreateWindow(m_width, m_height, m_windowName.c_str(), NULL, NULL);

			if (!m_window)
			{
				spdlog::error("Failed to create GLFW window");
				glfwTerminate();
				return;
			}
		}

		void Window::SetCallbackFunctions()
		{
			// TODO: Implement callbacks
		}

		void Window::Init()
		{
			InitGLFW();
			SetGLFWWindowHints();
			CreateWindow();
			// Make the context current
			glfwMakeContextCurrent(m_window);
			SetCallbackFunctions();
		}

		void Window::DeInit()
		{
			// Cleanup
			glfwDestroyWindow(m_window);
			glfwTerminate();
		}

		void Window::RunMainLoop()
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
	}
}