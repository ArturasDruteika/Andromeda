#ifndef CONTEXT__GLFW_CONTEXT__HPP
#define CONTEXT__GLFW_CONTEXT__HPP


#if defined(_WIN32)
	#if defined(CONTEXT_EXPORT)
		#define CONTEXT_API __declspec(dllexport)
	#else
	#define CONTEXT_API __declspec(dllimport)
#endif /* CONTEXT_API */
	#define _sprintf sprintf_s
#endif

#if defined(__GNUC__)
	// GCC
	#define CONTEXT_API __attribute__((visibility("default")))
#endif


#include "pch.hpp"
#include "GLFW/glfw3.h"


namespace Andromeda
{
	namespace Context
	{
		class CONTEXT_API GLFWContext
		{
		public:
			GLFWContext();
			~GLFWContext();

			GLFWContext(const GLFWContext& other) = delete;	// Prevent Copy Constructor
			GLFWContext& operator=(const GLFWContext& other) = delete;	// Prevent Copy assignment
			GLFWContext(GLFWContext&& other) noexcept = delete;	// Prevent Move constructor
			GLFWContext& operator=(const GLFWContext&& other) noexcept = delete;	//Prevent Move assignment

			void InitGLFW();
			void TerminateGLFW();
			void SetContextHints();
			void MakeContextCurrent(GLFWwindow* window);
			void SwapBuffers(GLFWwindow* window);

			bool IsInitialized();
			GLFWglproc GetGLFWglproc();
			
		private:
			class GLFWContextImpl;
			GLFWContextImpl* m_pGLFWContextImpl;
		};
	}
}


#endif // CONTEXT__GLFW_CONTEXT__HPP