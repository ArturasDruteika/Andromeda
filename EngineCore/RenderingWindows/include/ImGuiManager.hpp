#ifndef ENGINECORE__IMGUI_MANAGER__HPP
#define ENGINECORE__IMGUI_MANAGER__HPP


#include <imgui.h>
#include "GLFW/glfw3.h"


namespace Andromeda
{
	namespace EngineCore
	{
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
			void Render(unsigned int texture, int width, int height);
			void DeInit();

			bool IsInitialized() const;

		private:
			void InitImGui(GLFWwindow* window);

			bool m_isInitialized;
			ImGuiIO* m_io;
		};
	}
}


#endif // ENGINECORE__IMGUI_MANAGER__HPP