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

			bool IsInitialized() const;
			float GetWidth() const;
			float GetHeight() const;

		private:
			void InitImGui(GLFWwindow* window);

			bool m_isInitialized;
			ImVec2 m_windowSize;
			ImVec2 m_prevWindowSize; // Store previous size
			ImGuiIO* m_io;

			OnResizeCallback m_onResizeCallback;
		};
	}
}


#endif // ENGINECORE__IMGUI_MANAGER__HPP