#ifndef GLFW_WINDOW_HPP
#define GLFW_WINDOW_HPP

#include <GLFW/glfw3.h>
#include <functional>
#include "../../Events/include/FramebufferEvents.hpp"
#include "../../Events/include/KeyEvents.hpp"
#include "../../Events/include/MouseEvents.hpp"
#include "../../Events/include/EventDispatcher.hpp"
#include "spdlog/spdlog.h"


constexpr int DEFAULT_WINDOW_WIDTH = 640;
constexpr int DEFAULT_WINDOW_HEIGHT = 640;


namespace Andromeda
{
	namespace Window
	{
		class GLFWWindow
		{
		public:
			using EventCallbackFn = std::function<void(Window::Event&)>;

			GLFWWindow(
				int width = DEFAULT_WINDOW_WIDTH,
				int height = DEFAULT_WINDOW_HEIGHT,
				const std::string& windowName = "Andromeda Window",
				bool initWindow = true
			);
			~GLFWWindow();

			void Init();
			void DeInit();
			void CreateWindow();
			void SetCallbackFunctions();

			unsigned int GetWidth() const;
			unsigned int GetHeight() const;
			std::string GetWindowName() const;
			bool IsInitialized() const;
			GLFWwindow* GetWindow() const;

			void SetEventCallback(const EventCallbackFn& callback);

		private:
			// GLFW Callbacks
			static void ResizeWindow(GLFWwindow* window, int width, int height);
			static void WindowClose(GLFWwindow* window);
			static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
			static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
			static void MouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
			static void MouseMoveCallback(GLFWwindow* window, double xPos, double yPos);

			int m_width, m_height;
			std::string m_windowName;
			GLFWwindow* m_window;
			bool m_isInitialized;
			EventCallbackFn m_EventCallback;
		};
	}
}

#endif // GLFW_WINDOW_HPP
