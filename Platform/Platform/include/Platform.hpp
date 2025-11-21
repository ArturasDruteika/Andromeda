#ifndef PLATFORM__PLATFORM__PLATFORM__HPP
#define PLATFORM__PLATFORM__PLATFORM__HPP

#include "pch.hpp"

// Forward declaration of GLFWwindow (from GLFW)
struct GLFWwindow;

namespace Andromeda::Context
{
    class GLFWContext;
}

namespace Andromeda::Window
{
    class GLFWWindow;
}

namespace Andromeda::Platform
{
    class Platform
    {
    public:
        Platform();
        ~Platform();

        // Initialize GLFW, create window, make context current
        bool Init(int width, int height, const std::string& title);

        // Destroy window and terminate GLFW
        void Shutdown();

        // Poll OS/window events
        void PollEvents() const;

        // Check if window should close
        bool ShouldClose() const;

        // Swap front/back buffers
        void SwapBuffers() const;

        int GetWindowWidth() const;
        int GetWindowHeight() const;

        // Optional: expose native GLFW window if ImGui or other systems need it
        GLFWwindow* GetWindow() const;

    private:
        int m_width;
        int m_height;
        bool m_initialized;

        std::unique_ptr<Context::GLFWContext> m_pContext;
        std::unique_ptr<Window::GLFWWindow> m_pWindow;
    };
}

#endif // PLATFORM__PLATFORM__PLATFORM__HPP
