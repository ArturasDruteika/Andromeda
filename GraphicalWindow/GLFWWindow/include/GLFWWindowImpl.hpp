#ifndef WINDOW__WINDOW_IMPL__HPP
#define WINDOW__WINDOW_IMPL__HPP


#include "GLFWWindow.hpp"
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

			int GetWidth() const;
			int GetHeight() const;
			std::string GetWindowName() const;

		private:
			void InitGLFW();
			void SetGLFWWindowHints();
			void CreateWindow();
			void SetCallbackFunctions();

			bool m_isInitialized;
			int m_width;
			int m_height;
			std::string m_windowName;
			GLFWwindow* m_window;
			GLFWWindow& m_parent;
		};
	}
}


#endif // WINDOW__WINDOW_IMPL__HPP