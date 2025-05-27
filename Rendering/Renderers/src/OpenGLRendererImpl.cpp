#include "../include/OpenGLRendererImpl.hpp"
#include "../../Utils/include/MathUtils.hpp"
#include "FileOperations.hpp"
#include "Colors.hpp"
#include "glad/gl.h"
#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace Andromeda
{
	namespace Rendering
	{
        constexpr Space::Color BACKGROUND_COLOR_DEFAULT{ 0.0f, 0.0f, 0.1f, 1.0f };


        OpenGLRenderer::OpenGLRendererImpl::OpenGLRendererImpl()
            : m_isInitialized{ false }
            , m_shader{ nullptr }
            , m_FBO{ 0 }
            , m_FBOTexture{ 0 }
			, m_width{ 0 }
			, m_height{ 0 }
			, m_projectionMatrix{ glm::mat4(1.0f) }
			, m_pCamera{ nullptr }
			, m_depthBuffer{ 0 }
        {
            glClearColor(
                BACKGROUND_COLOR_DEFAULT.r,
                BACKGROUND_COLOR_DEFAULT.g,
                BACKGROUND_COLOR_DEFAULT.b,
                BACKGROUND_COLOR_DEFAULT.a
            );
            CreateShader();
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
            if (width <= 0 or height <= 0)
            {
				spdlog::error("Invalid dimensions for initialization: {}x{}", width, height);
                return;
            }

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
            glDeleteRenderbuffers(1, &m_depthBuffer);
            m_isInitialized = false;
        }

        void OpenGLRenderer::OpenGLRendererImpl::RenderFrame(const OpenGLScene& scene)
        {
            if (!m_isInitialized)
            {
                spdlog::error("Renderer is not initialized.");
                return;
            }

            // Bind the framebuffer
            glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
            glViewport(0, 0, m_width, m_height);

            // Clear both color and depth
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Make sure depth test/write are enabled
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LESS);
            glDepthMask(GL_TRUE);

            // Disable blending for opaque objects
            glDisable(GL_BLEND);

            // Use the shader program
            glUseProgram(m_shader->GetProgram());

            // Render all scene objects
            for (const auto& [id, object] : scene.GetObjects())
            {
                RenderObject(*object);
            }

            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        void OpenGLRenderer::OpenGLRendererImpl::Resize(int width, int height)
        {
			if (width <= 0 || height <= 0)
			{
				spdlog::error("Invalid dimensions for resizing: {}x{}", width, height);
				return;
			}
            else if (width == m_width && height == m_height)
            {
				spdlog::warn("Resize called with same dimensions: {}x{}", width, height);
				return;
            }

            m_width = width;
            m_height = height;

            glViewport(0, 0, width, height);
            glDeleteFramebuffers(1, &m_FBO);
            glDeleteTextures(1, &m_FBOTexture);
            glDeleteRenderbuffers(1, &m_depthBuffer); // Critical missing line

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

        unsigned int OpenGLRenderer::OpenGLRendererImpl::GetDepthBuffer() const
        {
            return m_depthBuffer;
        }

        int OpenGLRenderer::OpenGLRendererImpl::GetWidth() const
        {
            return m_width;
        }

        int OpenGLRenderer::OpenGLRendererImpl::GetHeight() const
        {
            return m_height;
        }

        void OpenGLRenderer::OpenGLRendererImpl::SetCamera(Camera* camera)
        {
			if (camera == nullptr)
			{
				spdlog::error("Camera is nullptr.");
				return;
			}
			m_pCamera = camera;
        }

        void OpenGLRenderer::OpenGLRendererImpl::InitFrameBuffer()
        {
            if (m_width <= 0 or m_height <= 0)
            {
                spdlog::warn("Cannot initialize framebuffer with dimensions: {}x{}", m_width, m_height);
                return;
            }
			GenerateAndBindFrameBuffer();
			GenerateAndBindFrameBufferTexture();
			ConfigureFrameBufferTexture();
			UnbindFrameBuffer();
            m_isInitialized = true;
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
            // 1. Generate FBO
			GenerateAndBindFrameBuffer();

            // 2. Create color texture
            glGenTextures(1, &m_FBOTexture);
            glBindTexture(GL_TEXTURE_2D, m_FBOTexture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_FBOTexture, 0);

            // 3. Create depth renderbuffer
            glGenRenderbuffers(1, &m_depthBuffer);
            glBindRenderbuffer(GL_RENDERBUFFER, m_depthBuffer);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, m_width, m_height);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthBuffer);

            // 4. Set draw buffer
            GLenum drawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
            glDrawBuffers(1, drawBuffers);

            // 5. Check FBO status
            GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
            if (status != GL_FRAMEBUFFER_COMPLETE)
            {
                spdlog::error("Framebuffer incomplete! Status: 0x{:X}", status); // hex
            }
        }

        void OpenGLRenderer::OpenGLRendererImpl::UnbindFrameBuffer() const
        {
            // Unbind the framebuffer
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        void OpenGLRenderer::OpenGLRendererImpl::RenderObject(const Rendering::IRenderableObjectOpenGL& object)
        {
            if (m_width == 0 || m_height == 0)
            {
                spdlog::error("Framebuffer dimensions are zero. Cannot render object.");
                return;
            }

            glm::mat4 viewMatrix = MathUtils::ToGLM(m_pCamera->GetViewMatrix());
            float aspect = static_cast<float>(m_width) / static_cast<float>(m_height);
            glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);
            glm::mat4 modelMatrix = MathUtils::ToGLM(object.GetModelMatrix());

            // Set common uniforms
            SetUniformMatrix4("u_model", modelMatrix);
            SetUniformMatrix4("u_view", viewMatrix);
            SetUniformMatrix4("u_projection", projectionMatrix);

            // Special case: light sphere
            if (object.GetIndicesCount() == 238800)
            {
                glm::vec3 lightWorldPos = MathUtils::ToGLM(object.GetCenterPosition());
                glm::vec3 cameraPos = MathUtils::ToGLM(m_pCamera->GetPosition());

                SetUniformVec3("u_lightPos", lightWorldPos);
                SetUniformVec3("u_viewPos", cameraPos);
                SetUniformVec3("u_lightColor", { 1.0f, 1.0f, 1.0f });

                // Force vertex color to white so it appears white
                SetUniformVec4("u_vertexColorOverride", MathUtils::ToGLM(object.GetColor().ReturnAsVec4()));
            }
            else
            {
                // Optional: reset override to no-op if your shader expects default value
                SetUniformVec4("u_vertexColorOverride", glm::vec4(0.0f));
            }

            glBindVertexArray(object.GetVAO());
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object.GetEBO());
            glDrawElements(GL_TRIANGLES, object.GetIndicesCount(), GL_UNSIGNED_INT, 0);
        }


        void OpenGLRenderer::OpenGLRendererImpl::SetUniformVec3(const std::string& name, const glm::vec3& vector)
        {
            int location = glGetUniformLocation(m_shader->GetProgram(), name.c_str());
            if (location == -1)
            {
                spdlog::warn("Uniform '{}' not found in shader.", name);
                return;
            }

            glUniform3f(location, vector.x, vector.y, vector.z);
        }

        void OpenGLRenderer::OpenGLRendererImpl::SetUniformVec4(const std::string& name, const glm::vec4& matrix)
        {
			int location = glGetUniformLocation(m_shader->GetProgram(), name.c_str());
			if (location == -1)
			{
				spdlog::warn("Uniform '{}' not found in shader.", name);
				return;
			}
			glUniform4f(location, matrix.r, matrix.g, matrix.b, matrix.a);
        }

        void OpenGLRenderer::OpenGLRendererImpl::SetUniformMatrix4(const std::string& name, const glm::mat4& matrix)
        {
            int location = glGetUniformLocation(m_shader->GetProgram(), name.c_str());
            if (location == -1)
            {
                spdlog::warn("Uniform '{}' not found in shader.", name);
                return;
            }

            glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
        }
	}
}
