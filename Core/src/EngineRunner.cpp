#include "EngineRunner.hpp"
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>


namespace Core
{
    EngineRunner::EngineRunner()
    {
    }

    EngineRunner::~EngineRunner()
    {
    }

    void EngineRunner::Run()
    {
        // Initialize GLFW
        if (!glfwInit()) {
            std::cerr << "Failed to initialize GLFW" << std::endl;
            return;
        }

        // Set GLFW window hints
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Request OpenGL 3.3
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required on macOS
#endif

        // Create a window
        GLFWwindow* window = glfwCreateWindow(640, 640, "LearnOpenGL", NULL, NULL);
        if (!window) {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return;
        }

        // Make the context current
        glfwMakeContextCurrent(window);

        // Load GLAD
        if (!gladLoadGL(glfwGetProcAddress)) {
            std::cerr << "Failed to initialize OpenGL context" << std::endl;
            glfwDestroyWindow(window);
            glfwTerminate();
            return;
        }

        // Print OpenGL information
        std::cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
        std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

        // Main loop
        while (!glfwWindowShouldClose(window)) {
            glClear(GL_COLOR_BUFFER_BIT);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        // Cleanup
        glfwDestroyWindow(window);
        glfwTerminate();
    }

}
