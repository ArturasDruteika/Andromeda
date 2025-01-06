#ifndef ENGINECORE__GLFW_CONTEXT__HPP
#define ENGINECORE__GLFW_CONTEXT__HPP


#include "pch.hpp"
#include "GLFW/glfw3.h"


namespace Andromeda
{
	namespace EngineCore
	{
		class GLFWContext
		{
		public:
			GLFWContext();
			~GLFWContext();

			void InitGLFW();
			void TerminateGLFW();
			void SetContextHints();
			void MakeContextCurrent(GLFWwindow* window);
			void SwapBuffers(GLFWwindow* window);

			bool IsInitialized();
			GLFWglproc GetGLFWglproc();
			
		private:
			bool m_isInitialized;
		};
	}
}


#endif // ENGINECORE__GLFW_CONTEXT__HPP