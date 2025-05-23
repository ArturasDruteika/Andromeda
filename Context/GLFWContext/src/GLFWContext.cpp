#include "../include/GLFWContext.hpp"


namespace Andromeda
{
	namespace Context
	{
		GLFWContext::GLFWContext()
			: m_isInitialized{ false }
		{
		}

		GLFWContext::~GLFWContext() = default;

		void GLFWContext::Init()
		{
			SetContextHints();
			m_isInitialized = true;
		}

		void GLFWContext::TerminateGLFW()
		{
			glfwTerminate();
			spdlog::info("GLFW terminated.");
			m_isInitialized = false;
		}

		void GLFWContext::SetContextHints()
		{
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

#ifdef __APPLE__
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required on macOS
#endif
		}

		void GLFWContext::MakeContextCurrent(GLFWwindow* window)
		{
			// Make the OpenGL context current
			glfwMakeContextCurrent(window);

			if (glfwGetCurrentContext() == nullptr)
			{
				spdlog::error("Failed to make OpenGL context current.");
				glfwDestroyWindow(window);
				glfwTerminate();
				return;
			}
		}

		void GLFWContext::SwapBuffers(GLFWwindow* window)
		{
			// Swap buffers and poll events
			glfwSwapBuffers(window);
		}

		bool GLFWContext::IsInitialized()
		{
			return m_isInitialized;
		}

		GLFWglproc GLFWContext::GetGLFWglproc()
		{
			return reinterpret_cast<GLFWglproc>(glfwGetProcAddress);
		}
	}
}
