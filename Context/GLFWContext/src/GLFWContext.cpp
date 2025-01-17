#include "../include/GLFWContext.hpp"
#include "../include/GLFWContextImpl.hpp"


namespace Andromeda
{
	namespace Context
	{
		GLFWContext::GLFWContext()
			: m_pGLFWContextImpl{ new GLFWContext::GLFWContextImpl() }
		{
		}

		GLFWContext::~GLFWContext()
		{
			delete m_pGLFWContextImpl;
		}

		void GLFWContext::InitGLFW()
		{
			m_pGLFWContextImpl->InitGLFW();
		}

		void GLFWContext::TerminateGLFW()
		{
			m_pGLFWContextImpl->TerminateGLFW();
		}

		void GLFWContext::SetContextHints()
		{
			m_pGLFWContextImpl->SetContextHints();
		}

		void GLFWContext::MakeContextCurrent(GLFWwindow* window)
		{
			m_pGLFWContextImpl->MakeContextCurrent(window);
		}

		void GLFWContext::SwapBuffers(GLFWwindow* window)
		{
			m_pGLFWContextImpl->SwapBuffers(window);
		}

		bool GLFWContext::IsInitialized()
		{
			return m_pGLFWContextImpl->IsInitialized();
		}

		GLFWglproc GLFWContext::GetGLFWglproc()
		{
			return m_pGLFWContextImpl->GetGLFWglproc();
		}
	}
}
