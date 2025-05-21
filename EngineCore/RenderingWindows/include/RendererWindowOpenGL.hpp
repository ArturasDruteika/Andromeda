#ifndef ENGINECORE__IMGUI_MANAGER__HPP
#define ENGINECORE__IMGUI_MANAGER__HPP


#include "pch.hpp"
#include "GraphicalModalWindow.hpp"
#include <imgui.h>
#include "GLFW/glfw3.h"


namespace Andromeda
{
	namespace EngineCore
	{
		using OnResizeCallback = std::function<void(int, int)>;
		using OnMouseMoveCallback = std::function<void(float, float, bool)>; // X, Y relative to content area
		using OnMouseScrollCallback = std::function<void(float)>;


		class RendererWindowOpenGL : public GraphicalModalWindow
		{
		public:
			RendererWindowOpenGL(int id, const std::string& windowName);
			~RendererWindowOpenGL();

			RendererWindowOpenGL(const RendererWindowOpenGL& other) = delete;	// Prevent Copy Constructor
			RendererWindowOpenGL& operator=(const RendererWindowOpenGL& other) = delete;	// Prevent Copy assignment
			RendererWindowOpenGL(RendererWindowOpenGL&& other) noexcept = delete;	// Prevent Move constructor
			RendererWindowOpenGL& operator=(const RendererWindowOpenGL&& other) noexcept = delete;	//Prevent Move assignment

			// Overrides from GraphicalModalWindow
			// Getters
			int GetID() override;
			float GetWindowWidth() override;
			float GetWindowHeight() override;
			float GetAvailableWindowWidth() override;
			float GetAvailableWindowHeight() override;
			std::string GetWindowName() override;
			// Setters
			void SetWindowName(const std::string& name) override;
			void Init() override;
			void Render() override;
			void DeInit() override;

			// Setters
			void SetTextureID(unsigned int textureID);

			void SetOnResizeCallback(OnResizeCallback callback);
			void SetOnMouseMoveCallback(OnMouseMoveCallback callback);
			void SetOnMouseScrollCallback(OnMouseScrollCallback callback);

			float GetWindowWidth() const;
			float GetWindowHeight() const;
			float GetAvailableWindowWidth() const;
			float GetAvailableWindowHeight() const;

		private:
			int m_id;
			unsigned int m_textureID;
			std::string m_windowName;
			ImVec2 m_windowSize;
			ImVec2 m_availableWindowSize;
			ImVec2 m_prevWindowSize;
			ImVec2 m_prevAvailableWindowSize;
			ImVec2 m_prevMousePos;
			ImGuiIO* m_io;

			OnResizeCallback m_onResizeCallback;
			OnMouseMoveCallback m_onMouseDragCallback;
			OnMouseScrollCallback m_onMouseScrollCallback;
		};
	}
}


#endif // ENGINECORE__IMGUI_MANAGER__HPP