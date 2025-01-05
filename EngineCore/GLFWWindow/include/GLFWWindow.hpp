#ifndef ENGINECORE__GLFW_WINDOW__HPP
#define ENGINECORE__GLFW_WINDOW__HPP


#if defined(_WIN32)
	#if defined(ENGINECORE_EXPORT)
		#define ENGINECORE_API __declspec(dllexport)
	#else
		#define ENGINECORE_API __declspec(dllimport)
	#endif /* ENGINECORE_API */
	#define _sprintf sprintf_s
#endif

#if defined(__GNUC__)
	// GCC
	#define ENGINECORE_API __attribute__((visibility("default")))
#endif

#include <string>


namespace Andromeda
{
	namespace EngineCore
	{
		class ENGINECORE_API GLFWWindow
		{
		public:
			GLFWWindow(int width = 640, int height = 640, const std::string& windowName = "Andromeda Window", bool initWindow = true);
			~GLFWWindow();

			void Init();
			void DeInit();
			void RunMainLoop();

			unsigned int GetWidth() const;
			unsigned int GetHeight() const;
			std::string GetWindowName() const;

		private:
			class GLFWWindowImpl;
			GLFWWindowImpl* m_pGLFWWindowImpl;
		};
	}
}


#endif // ENGINECORE__GLFW_WINDOW__HPP