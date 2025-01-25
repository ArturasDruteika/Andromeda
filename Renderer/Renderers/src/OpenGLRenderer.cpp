#include "../include/OpenGLRenderer.hpp"
#include "FileOperations.hpp"


namespace Andromeda
{
	namespace Renderer
	{
        OpenGLRenderer::OpenGLRenderer()
            : m_isInitialized{ false }
            , m_shader{ nullptr }
            , m_FBO{ 0 }
            , m_FBOTexture{ 0 }
        {
        }

        OpenGLRenderer::~OpenGLRenderer()
        {
            if (m_shader != nullptr)
            {
                delete m_shader;
            }
            glDeleteFramebuffers(1, &m_FBO);
            glDeleteTextures(1, &m_FBOTexture);
        }

        void OpenGLRenderer::Init()
        {
            // Initialize OpenGL-specific states
            glEnable(GL_DEPTH_TEST); // Enable depth testing for 3D rendering

            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            CreateShader();
            InitFrameBuffer(); // Initialize the framebuffer here
            m_isInitialized = true;
        }

        void OpenGLRenderer::DeInit()
        {
            // Cleanup resources
            if (m_shader != nullptr)
            {
                delete m_shader;
                m_shader = nullptr;
            }
            glDeleteFramebuffers(1, &m_FBO);
            glDeleteTextures(1, &m_FBOTexture);
            m_isInitialized = false;
        }

        void OpenGLRenderer::RenderFrame(const Environment::OpenGLScene& scene)
        {
            if (!m_isInitialized)
            {
                spdlog::error("Renderer is not initialized.");
                return;
            }

            // Bind the framebuffer for rendering
            glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
            glViewport(0, 0, 800, 600);
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the framebuffer

            // Use the shader program
            glUseProgram(m_shader->GetProgram());

            // Render all objects in the scene
            for (const auto& [id, object] : scene.GetObjects())
            {
                glBindVertexArray(object->GetVAO());
                glDrawArrays(GL_TRIANGLES, 0, object->GetVertexCount());
            }

            // Unbind the framebuffer
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        void OpenGLRenderer::ResizeViewport(int width, int height) const
        {
            if (width > 0 && height > 0) 
            {
                glViewport(0, 0, width, height);
                glBindTexture(GL_TEXTURE_2D, m_FBOTexture);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
                glBindTexture(GL_TEXTURE_2D, 0);
                spdlog::info("Viewport resized to {}x{}", width, height);
            }
        }

        bool OpenGLRenderer::IsInitialized() const
        {
            return m_isInitialized;
        }

        unsigned int OpenGLRenderer::GetFrameBufferObject() const
        {
            return m_FBO;
        }

        unsigned int OpenGLRenderer::GetFrameBufferObjectTexture() const
        {
            return m_FBOTexture;
        }

        void OpenGLRenderer::InitFrameBuffer()
        {
            // Generate and bind the framebuffer
            glGenFramebuffers(1, &m_FBO);
            glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

            // Generate and configure the texture for the framebuffer
            glGenTextures(1, &m_FBOTexture);
            glBindTexture(GL_TEXTURE_2D, m_FBOTexture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 800, 600, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_FBOTexture, 0);

            // Check if the framebuffer is complete
            if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            {
                spdlog::error("Framebuffer is not complete!");
            }

            // Unbind the framebuffer
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        void OpenGLRenderer::CreateShader()
        {
            std::string vertexShaderSource = Utils::FileOperations::LoadFileAsString("shader_program_sources/vertex_shader.glsl");
            std::string fragmentShaderSource = Utils::FileOperations::LoadFileAsString("shader_program_sources/fragment_shader.glsl");
            m_shader = new OpenGLShader(vertexShaderSource, fragmentShaderSource);
        }
	}
}
