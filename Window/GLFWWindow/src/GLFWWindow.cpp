#include "../include/GLFWWindow.hpp"
#include "../include/GLFWWindowImpl.hpp"


namespace Andromeda
{
	namespace Window
	{
		GLFWWindow::GLFWWindow(int width, int height, const std::string& windowName, bool initWindow)
			: m_pGLFWWindowImpl{ new GLFWWindow::GLFWWindowImpl(width, height, windowName, initWindow) }
		{
		}

		GLFWWindow::~GLFWWindow()
		{
			delete m_pGLFWWindowImpl;
		}

		void GLFWWindow::Init()
		{
			m_pGLFWWindowImpl->Init();
		}

		void GLFWWindow::DeInit()
		{
			m_pGLFWWindowImpl->DeInit();
		}

		unsigned int GLFWWindow::GetWidth() const
		{
			return m_pGLFWWindowImpl->GetWidth();
		}

		unsigned int GLFWWindow::GetHeight() const
		{
			return m_pGLFWWindowImpl->GetHeight();
		}

		std::string GLFWWindow::GetWindowName() const
		{
			return m_pGLFWWindowImpl->GetWindowName();
		}
		bool GLFWWindow::IsInitialized()
		{
			return m_pGLFWWindowImpl->IsInitialized();
		}
		GLFWwindow* GLFWWindow::GetWindow() const
		{
			return m_pGLFWWindowImpl->GetWindow();
		}

		void GLFWWindow::SetCallbackFunctions()
		{
			m_pGLFWWindowImpl->SetCallbackFunctions();
		}
	}
}