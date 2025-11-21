#ifndef CONTEXT__GLFW_CONTEXT__HPP
#define CONTEXT__GLFW_CONTEXT__HPP


#include "pch.hpp"
#include "GLFW/glfw3.h"


namespace Andromeda::GraphicsContext
{
	class GraphicsContextGLFW
	{
	public:
		GraphicsContextGLFW();
		~GraphicsContextGLFW();

		GraphicsContextGLFW(const GraphicsContextGLFW& other) = delete;	// Prevent Copy Constructor
		GraphicsContextGLFW& operator=(const GraphicsContextGLFW& other) = delete;	// Prevent Copy assignment
		GraphicsContextGLFW(GraphicsContextGLFW&& other) noexcept = delete;	// Prevent Move constructor
		GraphicsContextGLFW& operator=(const GraphicsContextGLFW&& other) noexcept = delete;	//Prevent Move assignment

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