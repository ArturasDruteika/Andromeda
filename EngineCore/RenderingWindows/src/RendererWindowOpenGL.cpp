#include "../include/RendererWindowOpenGL.hpp"
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>


namespace Andromeda
{
	namespace EngineCore
	{
		static ImVec2 SubtractImVec2(ImVec2 a, ImVec2 b)
		{
			return ImVec2(a.x - b.x, a.y - b.y);
		}

		RendererWindowOpenGL::RendererWindowOpenGL(int id, const std::string& windowName)
			: m_id{ id }
			, m_windowName{ windowName }
			, m_io{ nullptr }
			, m_prevMousePos{ ImVec2(-1.0f, -1.0f) }
			, m_textureID{ 0 }
		{
		}

		RendererWindowOpenGL::~RendererWindowOpenGL()
		{
			DeInit();
		}

		int RendererWindowOpenGL::GetID()
		{
			return m_id;
		}

		float RendererWindowOpenGL::GetWindowWidth()
		{
			return m_windowSize.x;
		}

		float RendererWindowOpenGL::GetWindowHeight()
		{
			return m_windowSize.y;
		}

		float RendererWindowOpenGL::GetAvailableWindowWidth()
		{
			return m_availableWindowSize.x;
		}

		float RendererWindowOpenGL::GetAvailableWindowHeight()
		{
			return m_availableWindowSize.y;
		}

		std::string RendererWindowOpenGL::GetWindowName()
		{
			return m_windowName;
		}

		void RendererWindowOpenGL::SetWindowName(const std::string& name)
		{
			m_windowName = name;
		}

		void RendererWindowOpenGL::Init()
		{
		}

		void RendererWindowOpenGL::Render()
		{
			// ImGui window
			ImGui::Begin(m_windowName.c_str(), 0, ImGuiWindowFlags_NoScrollbar);

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
					m_onMouseScrollCallback(-scrollY);
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

			ImGui::Image((ImTextureID)(intptr_t)m_textureID, ImVec2(m_availableWindowSize.x, m_availableWindowSize.y), ImVec2(0, 1), ImVec2(1, 0));
			ImGui::End();
		}

		void RendererWindowOpenGL::DeInit()
		{
		}

		void RendererWindowOpenGL::SetTextureID(unsigned int textureID)
		{
			m_textureID = textureID;
		}

		void RendererWindowOpenGL::SetOnResizeCallback(OnResizeCallback callback)
		{
			m_onResizeCallback = std::move(callback);
		}

		void RendererWindowOpenGL::SetOnMouseMoveCallback(OnMouseMoveCallback callback)
		{
			m_onMouseDragCallback = std::move(callback);
		}

		void RendererWindowOpenGL::SetOnMouseScrollCallback(OnMouseScrollCallback callback)
		{
			m_onMouseScrollCallback = std::move(callback);
		}

		float RendererWindowOpenGL::GetWindowWidth() const
		{
			return m_windowSize.x;
		}

		float RendererWindowOpenGL::GetWindowHeight() const
		{
			return m_windowSize.y;
		}

		float RendererWindowOpenGL::GetAvailableWindowWidth() const
		{
			return m_availableWindowSize.x;
		}

		float RendererWindowOpenGL::GetAvailableWindowHeight() const
		{
			return m_availableWindowSize.y;
		}
	}
}