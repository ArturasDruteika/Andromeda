#ifndef CONTEXT__GLFW_CONTEXT__HPP
#define CONTEXT__GLFW_CONTEXT__HPP


#include "pch.hpp"
#include "GLFW/glfw3.h"


namespace Andromeda::Context
{
	class GLFWContext
	{
	public:
		GLFWContext();
		~GLFWContext();

		GLFWContext(const GLFWContext& other) = delete;	// Prevent Copy Constructor
		GLFWContext& operator=(const GLFWContext& other) = delete;	// Prevent Copy assignment
		GLFWContext(GLFWContext&& other) noexcept = delete;	// Prevent Move constructor
		GLFWContext& operator=(const GLFWContext&& other) noexcept = delete;	//Prevent Move assignment

		void Init();
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


#endif // CONTEXT__GLFW_CONTEXT__HPP