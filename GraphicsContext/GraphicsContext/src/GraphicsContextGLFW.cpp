#include "../include/GraphicsContextGLFW.hpp"
#include "Window/WindowGLFW/include/WindowGLFW.hpp"
#include "spdlog/spdlog.h"


namespace Andromeda::GraphicsContext
{
	GraphicsContextGLFW::GraphicsContextGLFW()
		: m_isInitialized{ false }
		, m_pGLFWwindow{ nullptr }
	{
	}

	GraphicsContextGLFW::~GraphicsContextGLFW() = default;

	void GraphicsContextGLFW::Init(IWindow& window)
	{
		Window::WindowGLFW* pWindowGLFW = dynamic_cast<Window::WindowGLFW*>(&window);
		if (pWindowGLFW == nullptr)
		{
			spdlog::error("Failed to initialize GraphicsContextGLFW: Invalid window type.");
			return;
		}
		m_pGLFWwindow = static_cast<GLFWwindow*>(pWindowGLFW->GetNativeHandle());
		SetContextHints();
		m_isInitialized = true;
	}

	void GraphicsContextGLFW::MakeCurrent()
	{
		// Make the OpenGL context current
		glfwMakeContextCurrent(m_pGLFWwindow);

		if (glfwGetCurrentContext() == nullptr)
		{
			spdlog::error("Failed to make OpenGL context current.");
			glfwDestroyWindow(m_pGLFWwindow);
			glfwTerminate();
			return;
		}
	}

	void GraphicsContextGLFW::Present()
	{
		glfwSwapBuffers(m_pGLFWwindow);
	}

	//void GraphicsContextGLFW::TerminateGLFW()
	//{
	//	glfwTerminate();
	//	spdlog::info("GLFW terminated.");
	//	m_isInitialized = false;
	//}

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

	//bool GraphicsContextGLFW::IsInitialized()
	//{
	//	return m_isInitialized;
	//}

	//GLFWglproc GraphicsContextGLFW::GetGLFWglproc()
	//{
	//	return reinterpret_cast<GLFWglproc>(glfwGetProcAddress);
	//}
}
