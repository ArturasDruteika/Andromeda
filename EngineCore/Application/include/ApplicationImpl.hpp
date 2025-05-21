#ifndef ENGINECORE__APPLICATION_IMPL__HPP
#define ENGINECORE__APPLICATION_IMPL__HPP

#include "../include/Application.hpp"
#include "../../RenderingWindows/include/RendererWindowOpenGL.hpp"
#include "../../RenderingWindows/include/ImGuiDockspaceManager.hpp"
#include "OpenGLRenderer.hpp"
#include "OpenGLScene.hpp"
#include "OpenGLLoader.hpp"
#include "GLFWContext.hpp"
#include "GLFWWindow.hpp"
#include "Camera.hpp"
#include "CameraInputMapper.hpp"


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
			void AddToScene(int id, Rendering::IRenderableObjectOpenGL* object);
			void RemoveFromScene(int id);

		private:
			void InitGLFW();
			void SetupEventCallbacks();
			void SetupImGuiCallbacks();
			void OnMouseDragged(float x, float y, bool ctrlHeld);
			void OnMouseScroll(float scrollY);
			// Static event handlers
			static void EventCallback(Window::Event& event);

		private:
			bool m_isInitialized;
			Math::Vec2 m_LastMouseDragPos;
			Rendering::OpenGLLoader m_openGLLoader;
			Context::GLFWContext* m_pContext;
			Window::GLFWWindow* m_pWindow;
			Rendering::OpenGLRenderer* m_pRenderer;
			Rendering::OpenGLScene* m_pScene;
			RendererWindowOpenGL* m_pRendererWindowOpenGL;
			Rendering::Camera* m_pCamera;
			CameraInputMapper* m_pCameraInputMapper;
			ImGuiDockspaceManager* m_pImGuiDockspaceManager;
		};
	}
}

#endif // ENGINECORE__APPLICATION_IMPL__HPP
