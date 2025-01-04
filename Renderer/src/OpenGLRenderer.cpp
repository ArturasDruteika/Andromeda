#include "../include/OpenGLRenderer.hpp"


namespace Andromeda
{
	namespace Renderer
	{
		OpenGLRenderer::OpenGLRenderer()
			: m_VAO{ 0 }
			, m_VBO{ 0 }
			, m_program{ 0 }
			, m_isInitialized{ false }
		{
		}

		OpenGLRenderer::~OpenGLRenderer()
		{
		}

        bool OpenGLRenderer::IsInitialized() const
        {
            return m_isInitialized;
        }

		void OpenGLRenderer::Initialize()
		{
			m_isInitialized = true;
            // Initialize OpenGL-specific states
            glEnable(GL_DEPTH_TEST);
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

            // Set up the triangle
            SetupTriangle();
		}

		void OpenGLRenderer::RenderFrame()
		{
            // Clear the screen
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Render the triangle
            glUseProgram(m_program);
            glBindVertexArray(m_VAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);
		}

		void OpenGLRenderer::Shutdown()
		{
            // Cleanup resources
            glDeleteProgram(m_program);
            glDeleteBuffers(1, &m_VBO);
            glDeleteVertexArrays(1, &m_VAO);
			m_isInitialized = false;
		}

		void OpenGLRenderer::SetupTriangle()
		{
            // Vertex data for a triangle
            std::vector<float> vertices = {
                // Positions        // Colors
                0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // Top vertex (red)
               -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // Bottom left (green)
                0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f  // Bottom right (blue)
            };

            // Vertex shader source
            const char* vertexShaderSource = R"(
                #version 330 core
                layout(location = 0) in vec3 aPos;
                layout(location = 1) in vec3 aColor;

                out vec3 ourColor;

                void main()
                {
                    gl_Position = vec4(aPos, 1.0);
                    ourColor = aColor;
                }
            )";

            // Fragment shader source
            const char* fragmentShaderSource = R"(
                #version 330 core
                in vec3 ourColor;
                out vec4 FragColor;

                void main()
                {
                    FragColor = vec4(ourColor, 1.0);
                }
            )";

            // Compile shaders and link program
            m_program = CreateShaderProgram(vertexShaderSource, fragmentShaderSource);

            // Generate and bind VAO
            glGenVertexArrays(1, &m_VAO);
            glBindVertexArray(m_VAO);

            // Generate and bind VBO
            glGenBuffers(1, &m_VBO);
            glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

            // Vertex attribute pointers
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); // Position
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); // Color
            glEnableVertexAttribArray(1);

            // Unbind
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
		}

        GLuint OpenGLRenderer::CreateShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource)
        {
            GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
            glCompileShader(vertexShader);
            CheckCompileErrors(vertexShader, "VERTEX");

            GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
            glCompileShader(fragmentShader);
            CheckCompileErrors(fragmentShader, "FRAGMENT");

            GLuint shaderProgram = glCreateProgram();
            glAttachShader(shaderProgram, vertexShader);
            glAttachShader(shaderProgram, fragmentShader);
            glLinkProgram(shaderProgram);
            CheckCompileErrors(shaderProgram, "PROGRAM");

            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            return shaderProgram;
        }

        void OpenGLRenderer::CheckCompileErrors(GLuint shader, const std::string& type)
        {
            GLint success;
            GLchar infoLog[1024];
            if (type != "PROGRAM")
            {
                glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
                if (!success)
                {
                    glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
                    spdlog::error("Shader compilation error ({}): {}", type, infoLog);
                }
            }
            else
            {
                glGetProgramiv(shader, GL_LINK_STATUS, &success);
                if (!success)
                {
                    glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
                    spdlog::error("Program linking error: {}", infoLog);
                }
            }
        }
	}
}
