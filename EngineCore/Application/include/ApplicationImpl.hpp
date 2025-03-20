#ifndef ENGINECORE__APPLICATION_IMPL__HPP
#define ENGINECORE__APPLICATION_IMPL__HPP

#include "../include/Application.hpp"
#include "OpenGLRenderer.hpp"
#include "OpenGLScene.hpp"
#include "OpenGLLoader.hpp"
#include "../../RenderingWindows/include/ImGuiManager.hpp"
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
			void InitGLFW();
			void SetupEventCallbacks();
			void SetupImGuiCallbacks();

			//// Static event handlers
			static void EventCallback(Window::Event& event);

			bool m_isInitialized;
			Rendering::OpenGLLoader m_openGLLoader;
			Context::GLFWContext* m_pContext;
			Window::GLFWWindow* m_pWindow;
			Rendering::OpenGLRenderer* m_pRenderer;
			Rendering::OpenGLScene* m_pScene;
			ImGuiManager* m_pImGuiManager;
		};
	}
}

#endif // ENGINECORE__APPLICATION_IMPL__HPP
