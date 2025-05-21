#include "../include/ImGuiDockspaceManager.hpp"
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>


namespace Andromeda
{
	namespace EngineCore
	{
		ImGuiDockspaceManager::ImGuiDockspaceManager(GLFWwindow* window)
			: m_isInitialized{ false }
			, m_io{ nullptr }
			//, m_rendererWindowOpenGL{ nullptr }
		{
			InitImGui(window);
			Init();
		}

		ImGuiDockspaceManager::~ImGuiDockspaceManager()
		{
			DeInit();
		}

		bool ImGuiDockspaceManager::IsInitialized() const
		{
			return m_isInitialized;
		}

		void ImGuiDockspaceManager::Init()
		{
			if (!m_isInitialized)
			{
				//m_rendererWindowOpenGL = new RendererWindowOpenGL();
				m_isInitialized = true;
			}
			else
			{
				spdlog::info("ImGuiDockspaceManager is already initialized.");
			}
		}

		void ImGuiDockspaceManager::Render()
		{
			// Start ImGui frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			// Dockspace for ImGui
			ImGui::DockSpaceOverViewport(ImGui::GetMainViewport()->ID);

			RenderGraphicalModalWindows();

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

		void ImGuiDockspaceManager::DeInit()
		{
			// Cleanup
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
			ImGui::DestroyContext();
			m_isInitialized = false;
		}

		void ImGuiDockspaceManager::AddGraphicalModalWindow(int id, GraphicalModalWindow* window)
		{
			if (window == nullptr)
			{
				spdlog::error("GraphicalModalWindow is nullptr.");
				return;
			}
			m_graphicalModalWindows[id] = window;
		}

		void ImGuiDockspaceManager::InitImGui(GLFWwindow* window)
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

		void ImGuiDockspaceManager::RenderGraphicalModalWindows()
		{
			for (const auto& [id, window] : m_graphicalModalWindows)
			{
				if (window != nullptr)
				{
					window->Render();
				}
			}
		}
	}
}