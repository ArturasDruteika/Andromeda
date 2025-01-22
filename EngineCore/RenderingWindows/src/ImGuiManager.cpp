#include "../include/ImGuiManager.hpp"
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include "spdlog/spdlog.h"


namespace Andromeda
{
	namespace EngineCore
	{
		ImGuiManager::ImGuiManager(GLFWwindow* window, bool initialize)
			: m_io{ nullptr } // Initialize m_io as nullptr
			, m_isInitialized{ initialize }
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

		void ImGuiManager::Render()
		{
			// Start ImGui frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			// Dockspace for ImGui
			ImGui::DockSpaceOverViewport(ImGui::GetMainViewport()->ID);

			// ImGui window
			ImGui::Begin("Triangle Window");
			//ImGui::Image((ImTextureID)(intptr_t)fboTexture, ImVec2(800, 600), ImVec2(0, 1), ImVec2(1, 0));
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

		bool ImGuiManager::IsInitialized() const
		{
			return m_isInitialized;
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