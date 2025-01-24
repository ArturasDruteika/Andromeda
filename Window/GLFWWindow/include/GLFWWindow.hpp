#ifndef ENGINECORE__GLFW_WINDOW__HPP
#define ENGINECORE__GLFW_WINDOW__HPP


#include "pch.hpp"
#include "GLFW/glfw3.h"


namespace Andromeda
{
	namespace Window
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

			unsigned int GetWidth() const;
			unsigned int GetHeight() const;
			std::string GetWindowName() const;
			bool IsInitialized();
			GLFWwindow* GetWindow() const;
			void SetCallbackFunctions();

		private:
			void CreateWindow();

			bool m_isInitialized;
			int m_width;
			int m_height;
			std::string m_windowName;
			GLFWwindow* m_window;
		};
	}
}


#endif // ENGINECORE__GLFW_WINDOW__HPP