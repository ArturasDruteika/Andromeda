#ifndef ENGINECORE__GLFW_CONTEXT_IMPL__HPP
#define ENGINECORE__GLFW_CONTEXT_IMPL__HPP


#include "GLFWContext.hpp"


namespace Andromeda
{
	namespace Context
	{
		class GLFWContext::GLFWContextImpl
		{
		public:
			GLFWContextImpl();
			~GLFWContextImpl();

			GLFWContextImpl(const GLFWContextImpl& other) = delete;	// Prevent Copy Constructor
			GLFWContextImpl& operator=(const GLFWContextImpl& other) = delete;	// Prevent Copy assignment
			GLFWContextImpl(GLFWContextImpl&& other) noexcept = delete;	// Prevent Move constructor
			GLFWContextImpl& operator=(const GLFWContextImpl&& other) noexcept = delete;	//Prevent Move assignment

			void InitGLFW();
			void TerminateGLFW();
			void SetContextHints();
			void MakeContextCurrent(GLFWwindow* window);
			void SwapBuffers(GLFWwindow* window);

			bool IsInitialized();
			GLFWglproc GetGLFWglproc();
			
		private:
			bool m_isInitialized;
		};
	}
}


#endif // ENGINECORE__GLFW_CONTEXT_IMPL__HPP