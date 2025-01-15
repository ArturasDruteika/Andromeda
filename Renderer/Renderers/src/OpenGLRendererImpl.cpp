#include "../include/OpenGLRendererImpl.hpp"
#include "FileOperations.hpp"


namespace Andromeda
{
	namespace Renderer
	{
		OpenGLRenderer::OpenGLRendererImpl::OpenGLRendererImpl()
			: m_VAO{ 0 }
			, m_VBO{ 0 }
			, m_isInitialized{ false }
            , m_shader{ nullptr }
		{
		}

		OpenGLRenderer::OpenGLRendererImpl::~OpenGLRendererImpl()
		{
            if (m_shader != nullptr)
            {
                delete m_shader;
            }
		}

        bool OpenGLRenderer::OpenGLRendererImpl::IsInitialized() const
        {
            return m_isInitialized;
        }

		void OpenGLRenderer::OpenGLRendererImpl::Initialize(GLADloadfunc load)
		{
            LoadGlad(load);
			m_isInitialized = true;
            // Initialize OpenGL-specific states
            glEnable(GL_DEPTH_TEST);
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

            std::string vertexShaderSource = Utils::FileOperations::LoadFileAsString("shader_program_sources/vertex_shader.glsl");
            std::string fragmentShaderSource = Utils::FileOperations::LoadFileAsString("shader_program_sources/fragment_shader.glsl");

            m_shader = new OpenGLShader(vertexShaderSource, fragmentShaderSource);
		}

		void OpenGLRenderer::OpenGLRendererImpl::RenderFrame(const Environment::OpenGLScene& scene)
		{
            // Clear the screen
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glUseProgram(m_shader->GetProgram());
            for (const auto& object : scene.GetObjects())
            {
                glBindVertexArray(object->GetVAO());
                glDrawArrays(GL_TRIANGLES, 0, object->GetVertexCount());
            }
		}

		void OpenGLRenderer::OpenGLRendererImpl::Shutdown()
		{
            // Cleanup resources
            delete m_shader;
            m_shader = nullptr;
            glDeleteBuffers(1, &m_VBO);
            glDeleteVertexArrays(1, &m_VAO);
			m_isInitialized = false;
		}

        void OpenGLRenderer::OpenGLRendererImpl::LoadGlad(GLADloadfunc load)
        {
            if (!gladLoadGL(load))
            {
                spdlog::error("Failed to initialize GLAD.");
                return;
            }
            const char* version = reinterpret_cast<const char*>(glGetString(GL_VERSION));
            spdlog::info("GLAD initialized successfully. OpenGL version: {}", std::string(version));
        }

        void OpenGLRenderer::OpenGLRendererImpl::SetupTriangle()
		{
            // Vertex data for a triangle
            std::vector<float> vertices = {
                // Positions        // Colors
                0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // Top vertex (red)
               -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // Bottom left (green)
                0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f  // Bottom right (blue)
            };

            // TODO: move shader creation to init
            // Vertex shader source


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
	}
}
