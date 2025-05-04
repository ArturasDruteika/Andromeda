#include "../include/OpenGLRendererImpl.hpp"
#include "FileOperations.hpp"
#include "../../Utils/include/MathUtils.hpp"
#include "glad/gl.h"
#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace Andromeda
{
	namespace Rendering
	{
        OpenGLRenderer::OpenGLRendererImpl::OpenGLRendererImpl()
            : m_isInitialized{ false }
            , m_shader{ nullptr }
            , m_FBO{ 0 }
            , m_FBOTexture{ 0 }
			, m_width{ 0 }
			, m_height{ 0 }
        {
        }

        OpenGLRenderer::OpenGLRendererImpl::~OpenGLRendererImpl()
        {
            if (m_shader != nullptr)
            {
                delete m_shader;
            }
            glDeleteFramebuffers(1, &m_FBO);
            glDeleteTextures(1, &m_FBOTexture);
        }

        void OpenGLRenderer::OpenGLRendererImpl::Init(int width, int height)
        {
            // Initialize OpenGL-specific states
            glEnable(GL_DEPTH_TEST); // Enable depth testing for 3D rendering

            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            CreateShader();
			m_width = width;
			m_height = height;
            InitFrameBuffer();
            m_isInitialized = true;
        }

        void OpenGLRenderer::OpenGLRendererImpl::DeInit()
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

        void OpenGLRenderer::OpenGLRendererImpl::RenderFrame(const OpenGLScene& scene)
        {
            if (!m_isInitialized)
            {
                spdlog::error("Renderer is not initialized.");
                return;
            }

            // Bind the framebuffer for rendering
            glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
            glViewport(0, 0, m_width, m_height);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the framebuffer

            // Use the shader program
            glUseProgram(m_shader->GetProgram());

            // Render all objects in the scene
            for (const auto& [id, object] : scene.GetObjects())
            {
                RenderObject(*object);
            }

            // Unbind the framebuffer
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        void OpenGLRenderer::OpenGLRendererImpl::Resize(int width, int height)
        {
            if (width == m_width && height == m_height)
            {
                return; // No need to resize if dimensions are the same
            }

            m_width = width;
            m_height = height;

            glViewport(0, 0, width, height); // Update OpenGL viewport

            // Recreate the framebuffer to match new size
            glDeleteFramebuffers(1, &m_FBO);
            glDeleteTextures(1, &m_FBOTexture);
            InitFrameBuffer();
        }

        bool OpenGLRenderer::OpenGLRendererImpl::IsInitialized() const
        {
            return m_isInitialized;
        }

        unsigned int OpenGLRenderer::OpenGLRendererImpl::GetFrameBufferObject() const
        {
            return m_FBO;
        }

        unsigned int OpenGLRenderer::OpenGLRendererImpl::GetFrameBufferObjectTexture() const
        {
            return m_FBOTexture;
        }

        int OpenGLRenderer::OpenGLRendererImpl::GetWidth() const
        {
            return m_width;
        }

        int OpenGLRenderer::OpenGLRendererImpl::GetHeight() const
        {
            return m_height;
        }

        void OpenGLRenderer::OpenGLRendererImpl::InitFrameBuffer()
        {
			GenerateAndBindFrameBuffer();
			GenerateAndBindFrameBufferTexture();
			ConfigureFrameBufferTexture();
			UnbindFrameBuffer();
        }

        void OpenGLRenderer::OpenGLRendererImpl::CreateShader()
        {
            std::string vertexShaderFilePath = "shader_program_sources/vertex_shader.glsl";
			std::string fragmentShaderFilePath = "shader_program_sources/fragment_shader.glsl";
            std::string vertexShaderSource = Utils::FileOperations::LoadFileAsString(vertexShaderFilePath);
            std::string fragmentShaderSource = Utils::FileOperations::LoadFileAsString(fragmentShaderFilePath);
            m_shader = new OpenGLShader(vertexShaderSource, fragmentShaderSource);
        }

        void OpenGLRenderer::OpenGLRendererImpl::GenerateAndBindFrameBuffer()
        {
            // Generate and bind the framebuffer
            glGenFramebuffers(1, &m_FBO);
            glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
        }

        void OpenGLRenderer::OpenGLRendererImpl::GenerateAndBindFrameBufferTexture()
        {
            glGenTextures(1, &m_FBOTexture);
            glBindTexture(GL_TEXTURE_2D, m_FBOTexture);
        }

        void OpenGLRenderer::OpenGLRendererImpl::ConfigureFrameBufferTexture()
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_FBOTexture, 0);

            // Check if the framebuffer is complete
            if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            {
                spdlog::error("Framebuffer is not complete!");
            }
        }

        void OpenGLRenderer::OpenGLRendererImpl::UnbindFrameBuffer()
        {
            // Unbind the framebuffer
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        void OpenGLRenderer::OpenGLRendererImpl::RenderObject(const Rendering::IRenderableObjectOpenGL& object)
        {
            glm::mat4 dummyViewMatrix = glm::mat4(1.0f);
            glm::mat4 dummyProjectionMatrix = glm::mat4(1.0f);
            glm::mat4 modelMatrix = glm::mat4(1.0f);
            glBindVertexArray(object.GetVAO());
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object.GetEBO()); // Bind EBO
            glDrawElements(GL_TRIANGLES, object.GetVertexCount(), GL_UNSIGNED_INT, 0); // Use indices

            glUniformMatrix4fv(
                glGetUniformLocation(
                    m_shader->GetProgram(),
                    "u_modelMatrix"
                ),
                1,
                GL_FALSE,
                glm::value_ptr(modelMatrix)
            );
            glUniformMatrix4fv(
                glGetUniformLocation(
                    m_shader->GetProgram(),
                    "u_viewMatrix"
                ),
                1,
                GL_FALSE,
                glm::value_ptr(dummyViewMatrix)
            );
            glUniformMatrix4fv(
                glGetUniformLocation(
                    m_shader->GetProgram(),
                    "u_projectionMatrix"
                ),
                1,
                GL_FALSE,
                glm::value_ptr(dummyProjectionMatrix)
            );
        }

	}
}
