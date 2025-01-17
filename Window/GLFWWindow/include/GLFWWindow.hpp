#ifndef ENGINECORE__GLFW_WINDOW__HPP
#define ENGINECORE__GLFW_WINDOW__HPP


#if defined(_WIN32)
	#if defined(WINDOW_EXPORT)
		#define WINDOW_API __declspec(dllexport)
	#else
	#define WINDOW_API __declspec(dllimport)
#endif /* WINDOW_API */
	#define _sprintf sprintf_s
#endif

#if defined(__GNUC__)
	// GCC
	#define WINDOW_API __attribute__((visibility("default")))
#endif


#include "pch.hpp"
#include "GLFW/glfw3.h"


namespace Andromeda
{
	namespace Window
	{
		class WINDOW_API GLFWWindow
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

		private:
			class GLFWWindowImpl;
			GLFWWindowImpl* m_pGLFWWindowImpl;
		};
	}
}


#endif // ENGINECORE__GLFW_WINDOW__HPP