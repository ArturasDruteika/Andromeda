#ifndef WINDOW__WINDOW_IMPL__HPP
#define WINDOW__WINDOW_IMPL__HPP


#include "GLFWWindow.hpp"
#include "OpenGLRenderer.hpp"
#include "glad/gl.h"
#include <GLFW/glfw3.h>
#include <string>


namespace Andromeda
{
	namespace GraphicalWindow
	{
		class GLFWWindow::GLFWWindowImpl
		{
		public:
			GLFWWindowImpl(GLFWWindow& parent, int width = 640, int height = 640, const std::string& windowName = "Andromeda Window", bool initWindow = true);
			~GLFWWindowImpl();

			void Init();
			void DeInit();
			void RunMainLoop();

			unsigned int GetWidth() const;
			unsigned int GetHeight() const;
			std::string GetWindowName() const;

		private:
			void InitGLFW();
			void SetGLFWWindowHints();
			void CreateWindow();
			void SetCallbackFunctions();
			void GLFWMakeContextCurrent();
			void LoadGLAD();

			bool m_isInitialized;
			int m_width;
			int m_height;
			std::string m_windowName;
			GLFWwindow* m_window;
			GLFWWindow& m_parent;
			Renderer::OpenGLRenderer* m_renderer;
		};
	}
}


#endif // WINDOW__WINDOW_IMPL__HPP