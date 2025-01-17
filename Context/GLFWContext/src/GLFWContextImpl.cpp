#include "../include/GLFWContextImpl.hpp"


namespace Andromeda
{
	namespace Context
	{
		GLFWContext::GLFWContextImpl::GLFWContextImpl()
			: m_isInitialized{ false }
		{
		}

		GLFWContext::GLFWContextImpl::~GLFWContextImpl() = default;

		void GLFWContext::GLFWContextImpl::InitGLFW()
		{
			m_isInitialized = true;
			SetContextHints();
		}

		void GLFWContext::GLFWContextImpl::TerminateGLFW()
		{
			glfwTerminate();
			spdlog::info("GLFW terminated.");
			m_isInitialized = false;
		}

		void GLFWContext::GLFWContextImpl::SetContextHints()
		{
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required on macOS
#endif
		}

		void GLFWContext::GLFWContextImpl::MakeContextCurrent(GLFWwindow* window)
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

		void GLFWContext::GLFWContextImpl::SwapBuffers(GLFWwindow* window)
		{
			// Swap buffers and poll events
			glfwSwapBuffers(window);
		}

		bool GLFWContext::GLFWContextImpl::IsInitialized()
		{
			return m_isInitialized;
		}

		GLFWglproc GLFWContext::GLFWContextImpl::GetGLFWglproc()
		{
			return reinterpret_cast<GLFWglproc>(glfwGetProcAddress);
		}
	}
}
