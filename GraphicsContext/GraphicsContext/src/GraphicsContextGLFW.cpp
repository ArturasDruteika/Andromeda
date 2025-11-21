#include "../include/GraphicsContextGLFW.hpp"
#include "spdlog/spdlog.h"


namespace Andromeda::GraphicsContext
{
	GraphicsContextGLFW::GraphicsContextGLFW()
		: m_isInitialized{ false }
	{
	}

	GraphicsContextGLFW::~GraphicsContextGLFW() = default;

	void GraphicsContextGLFW::Init()
	{
		SetContextHints();
		m_isInitialized = true;
	}

	void GraphicsContextGLFW::TerminateGLFW()
	{
		glfwTerminate();
		spdlog::info("GLFW terminated.");
		m_isInitialized = false;
	}

	void GraphicsContextGLFW::SetContextHints()
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required on macOS
#endif
	}

	void GraphicsContextGLFW::MakeContextCurrent(GLFWwindow* window)
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

	void GraphicsContextGLFW::SwapBuffers(GLFWwindow* window)
	{
		// Swap buffers and poll events
		glfwSwapBuffers(window);
	}

	bool GraphicsContextGLFW::IsInitialized()
	{
		return m_isInitialized;
	}

	GLFWglproc GraphicsContextGLFW::GetGLFWglproc()
	{
		return reinterpret_cast<GLFWglproc>(glfwGetProcAddress);
	}
}
