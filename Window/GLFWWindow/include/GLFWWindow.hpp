#ifndef ENGINECORE__GLFW_WINDOW__HPP
#define ENGINECORE__GLFW_WINDOW__HPP


#include "pch.hpp"
#include "GLFW/glfw3.h"


constexpr int DEFAULT_WINDOW_WIDTH = 640;
constexpr int DEFAULT_WINDOW_HEIGHT = 640;


namespace Andromeda
{
	namespace Window
	{
		class GLFWWindow
		{
		public:
			GLFWWindow(
				int width = DEFAULT_WINDOW_WIDTH, 
				int height = DEFAULT_WINDOW_HEIGHT, 
				const std::string& windowName = "Andromeda Window", 
				bool initWindow = true
			);
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
			bool IsInitialized() const;
			GLFWwindow* GetWindow() const;
			void SetCallbackFunctions();

		private:
			void CreateWindow();
			static void ResizeWindow(GLFWwindow* window, int width, int height);

			bool m_isInitialized;
			int m_width;
			int m_height;
			std::string m_windowName;
			GLFWwindow* m_window;
		};
	}
}


#endif // ENGINECORE__GLFW_WINDOW__HPP