#ifndef WINDOW_WINDOW__HPP
#define WINDOW_WINDOW__HPP


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


#include <GLFW/glfw3.h>
#include <string>


namespace Andromeda
{
	namespace Window
	{
		class WINDOW_API Window
		{
		public:
			Window(int width = 640, int height = 640, const std::string& windowName = "Andromeda Window", bool initWindow = true);
			~Window();

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
		};
	}
}


#endif // WINDOW_WINDOW__HPP