#ifndef ENGINECORE__APPLICATION_IMPL__HPP
#define ENGINECORE__APPLICATION_IMPL__HPP


#include "../include/Application.hpp"
#include "OpenGLRenderer.hpp"
#include "OpenGLScene.hpp"

#include "GLFWContext.hpp"
#include "GLFWWindow.hpp"


namespace Andromeda
{
	namespace EngineCore
	{
		class Application::ApplicationImpl
		{
		public:
			ApplicationImpl();
			~ApplicationImpl();

			ApplicationImpl(const ApplicationImpl& other) = delete;	// Prevent Copy Constructor
			ApplicationImpl& operator=(const ApplicationImpl& other) = delete;	// Prevent Copy assignment
			ApplicationImpl(ApplicationImpl&& other) noexcept = delete;	// Prevent Move constructor
			ApplicationImpl& operator=(const ApplicationImpl&& other) noexcept = delete;	//Prevent Move assignment

			void Init();
			void RunMainLoop();
			void DeInit();

		private:
			bool m_isInitialized;
			Context::GLFWContext* m_context;
			Window::GLFWWindow* m_window;
			Renderer::OpenGLRenderer* m_renderer;
			Environment::OpenGLScene* m_scene;
		};
	}
}


#endif // ENGINECORE__APPLICATION_IMPL__HPP