#include "pch.hpp"
#include "../include/WindowGLFW.hpp"
#include "../../Events/include/FramebufferEvents.hpp"
#include "../../Events/include/KeyEvents.hpp"
#include "../../Events/include/MouseEvents.hpp"
#include "spdlog/spdlog.h"


namespace Andromeda::Window
{
	WindowGLFW::WindowGLFW(int width, int height, const std::string& title, bool initWindow)
		: m_width{ width }
		, m_height{ height }
		, m_title{ title }
		, m_window{ nullptr }
		, m_isInitialized{ false }
	{
		if (initWindow)
		{
			Init();
		}
	}

	WindowGLFW::~WindowGLFW()
	{
		DeInit();
	}

	bool WindowGLFW::IsInitialized() const
	{
		return m_isInitialized;
	}

	unsigned int WindowGLFW::GetWidth() const
	{
		return m_width;
	}

	unsigned int WindowGLFW::GetHeight() const
	{
		return m_height;
	}

	std::string WindowGLFW::GetTitle() const
	{
		return m_title;
	}

	void WindowGLFW::SetTitle(const std::string& title)
	{
		m_title = title;
	}

	void WindowGLFW::PollEvents()
	{
		glfwPollEvents();
	}

	bool WindowGLFW::ShouldClose() const
	{
		if (!m_window)
		{
			// If there is no window, treat it as "should close"
			return true;
		}

		return glfwWindowShouldClose(m_window) != 0;
	}

	void* WindowGLFW::GetNativeHandle() const
	{
		// This is what your GraphicsContextGLFW will cast back to GLFWwindow*
		return static_cast<void*>(m_window);
	}

	void WindowGLFW::Init()
	{
		if (!m_isInitialized)
		{
			try
			{
				CreateNewWindow();
				SetCallbackFunctions();
				m_isInitialized = true;
			}
			catch (const std::exception& e)
			{
				spdlog::error("Initialization failed: {}", e.what());
				DeInit();
			}
		}
	}

	void WindowGLFW::DeInit()
	{
		if (m_isInitialized)
		{
			glfwDestroyWindow(m_window);
			m_isInitialized = false;
		}
	}

	void WindowGLFW::CreateNewWindow()
	{
		m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);

		if (!m_window)
		{
			spdlog::error("Failed to create GLFW window.");
			return;
		}

		// Associate this instance with the GLFW window
		glfwSetWindowUserPointer(m_window, this);
	}

	void WindowGLFW::SetCallbackFunctions()
	{
		glfwSetFramebufferSizeCallback(m_window, ResizeWindow);
		glfwSetWindowCloseCallback(m_window, WindowClose);
		glfwSetKeyCallback(m_window, KeyCallback);
		glfwSetMouseButtonCallback(m_window, MouseButtonCallback);
		glfwSetScrollCallback(m_window, MouseScrollCallback);
		glfwSetCursorPosCallback(m_window, MouseMoveCallback);
	}

	GLFWwindow* WindowGLFW::GetWindow() const
	{
		return m_window;
	}

	void WindowGLFW::SetEventCallback(const EventCallbackFn& callback)
	{
		m_EventCallback = callback;
	}

	void WindowGLFW::ResizeWindow(GLFWwindow* window, int width, int height)
	{
		WindowGLFW* instance = static_cast<WindowGLFW*>(glfwGetWindowUserPointer(window));
		if (instance)
		{
			instance->m_width = width;
			instance->m_height = height;
			// spdlog::debug("Window resized to {}x{}", width, height);

			if (instance->m_EventCallback)
			{
				WindowResizeEvent event(width, height);
				instance->m_EventCallback(event);
			}
		}
	}

	void WindowGLFW::WindowClose(GLFWwindow* window)
	{
		WindowGLFW* instance = static_cast<WindowGLFW*>(glfwGetWindowUserPointer(window));
		if (instance)
		{
			// spdlog::debug("Window close event triggered.");
			if (instance->m_EventCallback)
			{
				WindowCloseEvent event;
				instance->m_EventCallback(event);
			}
		}
	}

	void WindowGLFW::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		WindowGLFW* instance = static_cast<WindowGLFW*>(glfwGetWindowUserPointer(window));
		if (instance)
		{
			if (instance->m_EventCallback)
			{
				if (action == GLFW_PRESS || action == GLFW_REPEAT)
				{
					KeyPressedEvent event(static_cast<KeyCode>(key), action == GLFW_REPEAT);
					// spdlog::debug("Key Pressed: {} (Repeat: {})", key, action == GLFW_REPEAT);
					instance->m_EventCallback(event);
				}
				else if (action == GLFW_RELEASE)
				{
					KeyReleasedEvent event(static_cast<KeyCode>(key));
					// spdlog::debug("Key Released: {}", key);
					instance->m_EventCallback(event);
				}
			}
		}
	}

	void WindowGLFW::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		WindowGLFW* instance = static_cast<WindowGLFW*>(glfwGetWindowUserPointer(window));
		if (instance)
		{
			if (instance->m_EventCallback)
			{
				if (action == GLFW_PRESS)
				{
					MouseButtonPressedEvent event(static_cast<MouseCode>(button));
					// spdlog::debug("Mouse Button Pressed: {}", button);
					instance->m_EventCallback(event);
				}
				else if (action == GLFW_RELEASE)
				{
					MouseButtonReleasedEvent event(static_cast<MouseCode>(button));
					// spdlog::debug("Mouse Button Released: {}", button);
					instance->m_EventCallback(event);
				}
			}
		}
	}

	void WindowGLFW::MouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
	{
		WindowGLFW* instance = static_cast<WindowGLFW*>(glfwGetWindowUserPointer(window));
		if (instance)
		{
			if (instance->m_EventCallback)
			{
				MouseScrolledEvent event(static_cast<float>(xOffset), static_cast<float>(yOffset));
				// spdlog::debug("Mouse Scrolled: X Offset = {}, Y Offset = {}", xOffset, yOffset);
				instance->m_EventCallback(event);
			}
		}
	}

	void WindowGLFW::MouseMoveCallback(GLFWwindow* window, double xPos, double yPos)
	{
		WindowGLFW* instance = static_cast<WindowGLFW*>(glfwGetWindowUserPointer(window));
		if (instance)
		{
			if (instance->m_EventCallback)
			{
				MouseMovedEvent event(static_cast<float>(xPos), static_cast<float>(yPos));
				// spdlog::debug("Mouse Moved: X = {}, Y = {}", xPos, yPos);
				instance->m_EventCallback(event);
			}
		}
	}
}
