#ifndef ENGINECORE__GLFW_WINDOW__HPP
#define ENGINECORE__GLFW_WINDOW__HPP


#include "pch.hpp"


namespace Andromeda
{
	namespace EngineCore
	{
		class GLFWWindow
		{
		public:
			GLFWWindow(int width = 640, int height = 640, const std::string& windowName = "Andromeda Window", bool initWindow = true);
			~GLFWWindow();

			GLFWWindow(const GLFWWindow& other) = delete;	// Prevent Copy Constructor
			GLFWWindow& operator=(const GLFWWindow& other) = delete;	// Prevent Copy assignment
			GLFWWindow(GLFWWindow&& other) noexcept = delete;	// Prevent Move constructor
			GLFWWindow& operator=(const GLFWWindow&& other) noexcept = delete;	//Prevent Move assignment

			void Init();
			void DeInit();
			void RunMainLoop();

			unsigned int GetWidth() const;
			unsigned int GetHeight() const;
			std::string GetWindowName() const;
			bool IsInitialized();

		private:
			class GLFWWindowImpl;
			GLFWWindowImpl* m_pGLFWWindowImpl;
		};
	}
}


#endif // ENGINECORE__GLFW_WINDOW__HPP