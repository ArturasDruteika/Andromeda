#ifndef CONTEXT__GLFW_CONTEXT__HPP
#define CONTEXT__GLFW_CONTEXT__HPP


#include "Andromeda/GraphicsContext/IGraphicsContext.hpp"
#include "Andromeda/Window/IWindow.hpp"
#include "glad/gl.h"
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

		bool IsInitialized() const override;
		bool Init(IWindow& window) override;
		void MakeCurrent() override;
		void Present() override;
		void SetContextHints();

	private:
		bool LoadGlad();

	private:
		bool m_initialized;
		GLFWwindow* m_pGLFWwindow;
	};
}


#endif // CONTEXT__GLFW_CONTEXT__HPP