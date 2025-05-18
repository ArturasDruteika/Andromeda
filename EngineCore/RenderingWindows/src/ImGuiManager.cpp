#include "../include/ImGuiManager.hpp"
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include "spdlog/spdlog.h"


namespace Andromeda
{
	namespace EngineCore
	{
		static ImVec2 SubtractImVec2(ImVec2 a, ImVec2 b)
		{
			return ImVec2(a.x - b.x, a.y - b.y);
		}

		ImGuiManager::ImGuiManager(GLFWwindow* window, bool initialize)
			: m_io{ nullptr } // Initialize m_io as nullptr
			, m_isInitialized{ initialize }
			, m_prevMousePos{ ImVec2(-1.0f, -1.0f) }
		{
			if (initialize)
			{
				Init(window);
			}
		}

		ImGuiManager::~ImGuiManager()
		{
		}

		void ImGuiManager::Init(GLFWwindow* window)
		{
			if (!m_isInitialized)
			{
				InitImGui(window);
				m_isInitialized = true;
			}
			else
			{
				spdlog::info("ImGuiManager is already initialized.");
			}
		}

		void ImGuiManager::Render(unsigned int texture)
		{
			// Start ImGui frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			// Dockspace for ImGui
			ImGui::DockSpaceOverViewport(ImGui::GetMainViewport()->ID);

			// ImGui window
			ImGui::Begin("Renderer", 0, ImGuiWindowFlags_NoScrollbar);

			m_windowSize = ImGui::GetWindowSize();
			m_availableWindowSize = ImGui::GetContentRegionAvail();

			if (ImGui::IsWindowHovered(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem) &&
				ImGui::IsMouseDragging(ImGuiMouseButton_Left))
			{
				ImVec2 localMousePos = ImVec2(
					ImGui::GetMousePos().x - ImGui::GetCursorScreenPos().x,
					ImGui::GetMousePos().y - ImGui::GetCursorScreenPos().y
				);

				bool ctrlHeld = ImGui::GetIO().KeyCtrl;

				// Clamp to content area
				ImVec2 contentSize = ImGui::GetContentRegionAvail();
				localMousePos.x = std::clamp(localMousePos.x, 0.0f, contentSize.x);
				localMousePos.y = std::clamp(localMousePos.y, 0.0f, contentSize.y);

				// Fire callback only if mouse actually moved
				if (localMousePos.x != m_prevMousePos.x || localMousePos.y != m_prevMousePos.y)
				{
					if (m_onMouseDragCallback)
					{
						m_onMouseDragCallback(localMousePos.x, localMousePos.y, ctrlHeld);
					}
					m_prevMousePos = localMousePos;
				}
			}

			if (ImGui::IsWindowHovered(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem))
			{
				float scrollY = ImGui::GetIO().MouseWheel;
				if (scrollY != 0.0f && m_onMouseScrollCallback)
				{
					m_onMouseScrollCallback(scrollY);
				}
			}

			// Check if the size has changed
			if (m_availableWindowSize.x != m_prevAvailableWindowSize.x || m_availableWindowSize.y != m_prevAvailableWindowSize.y)
			{
				m_prevAvailableWindowSize = m_availableWindowSize;
				if (m_onResizeCallback)
				{
					m_onResizeCallback(static_cast<int>(m_availableWindowSize.x), static_cast<int>(m_availableWindowSize.y));
				}
			}

			ImGui::Image((ImTextureID)(intptr_t)texture, ImVec2(m_availableWindowSize.x, m_availableWindowSize.y), ImVec2(0, 1), ImVec2(1, 0));
			ImGui::End();

			// Render ImGui
			glDisable(GL_DEPTH_TEST); // Disable depth testing for ImGui
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			// Update and render additional platform windows
			if (m_io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				GLFWwindow* backup_current_context = glfwGetCurrentContext();
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();
				glfwMakeContextCurrent(backup_current_context);
			}
		}

		void ImGuiManager::DeInit()
		{
			// Cleanup
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
			ImGui::DestroyContext();
			m_isInitialized = false;
		}

		void ImGuiManager::SetOnResizeCallback(OnResizeCallback callback)
		{
			m_onResizeCallback = std::move(callback);
		}

		void ImGuiManager::SetOnMouseMoveCallback(OnMouseMoveCallback callback)
		{
			m_onMouseDragCallback = std::move(callback);
		}

		void ImGuiManager::SetOnMouseScrollCallback(OnMouseScrollCallback callback)
		{
			m_onMouseScrollCallback = std::move(callback);
		}

		bool ImGuiManager::IsInitialized() const
		{
			return m_isInitialized;
		}

		float ImGuiManager::GetWindowWidth() const
		{
			return m_windowSize.x;
		}

		float ImGuiManager::GetWindowHeight() const
		{
			return m_windowSize.y;
		}

		float ImGuiManager::GetAvailableWindowWidth() const
		{
			return m_availableWindowSize.x;
		}

		float ImGuiManager::GetAvailableWindowHeight() const
		{
			return m_availableWindowSize.y;
		}

		void ImGuiManager::InitImGui(GLFWwindow* window)
		{
			// Initialize ImGui
			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			m_io = &ImGui::GetIO();
			m_io->ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking
			m_io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform Windows

			// Setup Dear ImGui style
			ImGui::StyleColorsDark();

			// Setup Platform/Renderer bindings
			ImGui_ImplGlfw_InitForOpenGL(window, true);
			ImGui_ImplOpenGL3_Init("#version 450");
		}
	}
}