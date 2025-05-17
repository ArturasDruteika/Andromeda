#ifndef ENGINECORE__IMGUI_MANAGER__HPP
#define ENGINECORE__IMGUI_MANAGER__HPP


#include "pch.hpp"
#include <imgui.h>
#include "GLFW/glfw3.h"


namespace Andromeda
{
	namespace EngineCore
	{
		using OnResizeCallback = std::function<void(int, int)>;  // Define a callback type
		using OnMouseMoveCallback = std::function<void(float, float, bool)>; // X, Y relative to content area

		class ImGuiManager
		{
		public:
			ImGuiManager(GLFWwindow* window, bool initialize = false);
			~ImGuiManager();

			ImGuiManager(const ImGuiManager& other) = delete;	// Prevent Copy Constructor
			ImGuiManager& operator=(const ImGuiManager& other) = delete;	// Prevent Copy assignment
			ImGuiManager(ImGuiManager&& other) noexcept = delete;	// Prevent Move constructor
			ImGuiManager& operator=(const ImGuiManager&& other) noexcept = delete;	//Prevent Move assignment

			void Init(GLFWwindow* window);
			void Render(unsigned int texture);
			void DeInit();
			void SetOnResizeCallback(OnResizeCallback callback);
			void SetOnMouseMoveCallback(OnMouseMoveCallback callback);

			bool IsInitialized() const;
			float GetWindowWidth() const;
			float GetWindowHeight() const;
			float GetAvailableWindowWidth() const;
			float GetAvailableWindowHeight() const;

		private:
			void InitImGui(GLFWwindow* window);

			bool m_isInitialized;
			ImVec2 m_windowSize;
			ImVec2 m_availableWindowSize;
			ImVec2 m_prevWindowSize; // Store previous size
			ImVec2 m_prevAvailableWindowSize; // Store previous size
			ImVec2 m_prevMousePos; // Sentinel to force initial trigger
			ImGuiIO* m_io;

			OnResizeCallback m_onResizeCallback;
			OnMouseMoveCallback m_onMouseDragCallback;
		};
	}
}


#endif // ENGINECORE__IMGUI_MANAGER__HPP