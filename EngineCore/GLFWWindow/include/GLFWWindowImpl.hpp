#ifndef ENGINECORE__WINDOW_IMPL__HPP
#define ENGINECORE__WINDOW_IMPL__HPP


#include "GLFWWindow.hpp"
#include "OpenGLRenderer.hpp"
#include "../../GLFWContext/include/GLFWContext.hpp"


namespace Andromeda
{
	namespace EngineCore
	{
		class GLFWWindow::GLFWWindowImpl
		{
		public:
			GLFWWindowImpl(GLFWWindow& parent, int width = 640, int height = 640, const std::string& windowName = "Andromeda Window", bool initWindow = true);
			~GLFWWindowImpl();

			GLFWWindowImpl(const GLFWWindowImpl& other) = delete;	// Prevent Copy Constructor
			GLFWWindowImpl& operator=(const GLFWWindowImpl& other) = delete;	// Prevent Copy assignment
			GLFWWindowImpl(GLFWWindowImpl&& other) noexcept = delete;	// Prevent Move constructor
			GLFWWindowImpl& operator=(const GLFWWindowImpl&& other) noexcept = delete;	//Prevent Move assignment

			void Init();
			void DeInit();
			void RunMainLoop();

			unsigned int GetWidth() const;
			unsigned int GetHeight() const;
			std::string GetWindowName() const;
			bool IsInitialized();

		private:
			void CreateWindow();
			void SetCallbackFunctions();

			bool m_isInitialized;
			int m_width;
			int m_height;
			std::string m_windowName;
			GLFWwindow* m_window;
			GLFWContext* m_context;
			GLFWWindow& m_parent;
			Renderer::OpenGLRenderer* m_renderer;
		};
	}
}


#endif // ENGINECORE__WINDOW_IMPL__HPP