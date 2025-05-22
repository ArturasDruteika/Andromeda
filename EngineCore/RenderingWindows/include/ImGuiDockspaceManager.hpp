#ifndef ENGINECORE__IMGUI_DOCKSPACE_MANAGER__HPP
#define ENGINECORE__IMGUI_DOCKSPACE_MANAGER__HPP


#include "pch.hpp"
#include "GraphicalModalWindow.hpp"
#include "RendererWindowOpenGL.hpp"
#include <imgui.h>
#include "GLFW/glfw3.h"


namespace Andromeda
{
	namespace EngineCore
	{
		class ImGuiDockspaceManager
		{
		public:
			ImGuiDockspaceManager(GLFWwindow* window);
			~ImGuiDockspaceManager();

			ImGuiDockspaceManager(const ImGuiDockspaceManager& other) = delete;	// Prevent Copy Constructor
			ImGuiDockspaceManager& operator=(const ImGuiDockspaceManager& other) = delete;	// Prevent Copy assignment
			ImGuiDockspaceManager(ImGuiDockspaceManager&& other) noexcept = delete;	// Prevent Move constructor
			ImGuiDockspaceManager& operator=(const ImGuiDockspaceManager&& other) noexcept = delete;	//Prevent Move assignment

			// Getters
			bool IsInitialized() const;

			void Init();
			void Render();
			void DeInit();
			void AddGraphicalModalWindow(int id, GraphicalModalWindow* window);
			void SetTexture(unsigned int texture);

		private:
			void InitImGui(GLFWwindow* window);
			void RenderGraphicalModalWindows();
			void DeleteGraphicalModalWindows();

		private:
			bool m_isInitialized;
			RendererWindowOpenGL* m_rendererWindowOpenGL;
			std::unordered_map<int, GraphicalModalWindow*> m_graphicalModalWindows;
			ImGuiIO* m_io;
		};
	}
}


#endif // ENGINECORE__IMGUI_DOCKSPACE_MANAGER__HPP