#ifndef WINDOW__GLFW_WINDOW__HPP_HPP
#define WINDOW__GLFW_WINDOW__HPP_HPP


#include "../../Events/include/Event.hpp"
#include "Window/IWindow.hpp"
#include <GLFW/glfw3.h>
#include <functional>


constexpr int DEFAULT_WINDOW_WIDTH = 640;
constexpr int DEFAULT_WINDOW_HEIGHT = 640;


namespace Andromeda::Window
{
	class WindowGLFW
		: public IWindow
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		WindowGLFW(
			int width = DEFAULT_WINDOW_WIDTH,
			int height = DEFAULT_WINDOW_HEIGHT,
			const std::string& title = "Andromeda Window",
			bool initWindow = true
		);
		~WindowGLFW() override;

		bool IsInitialized() const override;
		unsigned int GetWidth() const override;
		unsigned int GetHeight() const override;
		std::string GetTitle() const;
		void SetTitle(const std::string& title) override;
		virtual void PollEvents() override;
		virtual bool ShouldClose() const override;
		virtual void* GetNativeHandle() const override;

		GLFWwindow* GetWindow() const;

		void Init();
		void DeInit();
		void CreateNewWindow();
		void SetCallbackFunctions();
		void SetEventCallback(const EventCallbackFn& callback);

	private:
		// GLFW Callbacks
		static void ResizeWindow(GLFWwindow* window, int width, int height);
		static void WindowClose(GLFWwindow* window);
		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		static void MouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
		static void MouseMoveCallback(GLFWwindow* window, double xPos, double yPos);

	private:
		bool m_isInitialized;
		int m_width, m_height;
		std::string m_title;
		EventCallbackFn m_EventCallback;
		GLFWwindow* m_window;
	};
}

#endif // WINDOW__GLFW_WINDOW__HPP_HPP
