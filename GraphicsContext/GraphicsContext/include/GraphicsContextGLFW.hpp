#ifndef CONTEXT__GLFW_CONTEXT__HPP
#define CONTEXT__GLFW_CONTEXT__HPP


#include "GraphicsContext/IGraphicsContext.hpp"
#include "Window/IWindow.hpp"
#include "GLFW/glfw3.h"


namespace Andromeda::GraphicsContext
{
	class GraphicsContextGLFW
		: public IGraphicsContext
	{
	public:
		GraphicsContextGLFW();
		~GraphicsContextGLFW() override;

		GraphicsContextGLFW(const GraphicsContextGLFW& other) = delete;	// Prevent Copy Constructor
		GraphicsContextGLFW& operator=(const GraphicsContextGLFW& other) = delete;	// Prevent Copy assignment
		GraphicsContextGLFW(GraphicsContextGLFW&& other) noexcept = delete;	// Prevent Move constructor
		GraphicsContextGLFW& operator=(const GraphicsContextGLFW&& other) noexcept = delete;	//Prevent Move assignment

		void Init(IWindow& window) override;
		void MakeCurrent() override;
		void Present() override;

		//void TerminateGLFW();
		void SetContextHints();

		//bool IsInitialized();
		//GLFWglproc GetGLFWglproc();

	private:
		bool m_isInitialized;
		GLFWwindow* m_pGLFWwindow;
	};
}


#endif // CONTEXT__GLFW_CONTEXT__HPP