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
        constexpr Space::Color BACKGROUND_COLOR_DEFAULT{ 0.0f, 0.0f, 0.0f, 1.0f };


        OpenGLRenderer::OpenGLRendererImpl::OpenGLRendererImpl()
            : m_isInitialized{ false }
            , m_FBO{ 0 }
            , m_FBOTexture{ 0 }
			, m_width{ 0 }
			, m_height{ 0 }
			, m_projectionMatrix{ glm::mat4(1.0f) }
			, m_pCamera{ nullptr }
			, m_depthBuffer{ 0 }
			, m_ambientStrength{ 0.1f }
			, m_specularStrength{ 0.5f }
			, m_shininess{ 32.0f }
        {
            glClearColor(
                BACKGROUND_COLOR_DEFAULT.r,
                BACKGROUND_COLOR_DEFAULT.g,
                BACKGROUND_COLOR_DEFAULT.b,
                BACKGROUND_COLOR_DEFAULT.a
            );
            InitShaders();
        }

        OpenGLRenderer::OpenGLRendererImpl::~OpenGLRendererImpl()
        {
            DeInit();
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
            for (const auto& [shaderType, shader] : m_shadersMap)
            {
                if (shader != nullptr)
                {
                    delete shader;
                }
            }
            m_shadersMap.clear();
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
            glDeleteRenderbuffers(1, &m_depthBuffer);

            InitFrameBuffer();
        }

        void OpenGLRenderer::OpenGLRendererImpl::ShowGrid(bool show)
        {
			m_showGrid = show;
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

        float OpenGLRenderer::OpenGLRendererImpl::GetAmbientStrength() const
        {
            return m_ambientStrength;
        }

        float OpenGLRenderer::OpenGLRendererImpl::GetSpecularStrength() const
        {
            return m_specularStrength;
        }

        float OpenGLRenderer::OpenGLRendererImpl::GetShininess() const
        {
            return m_shininess;
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

        void OpenGLRenderer::OpenGLRendererImpl::SetAmbientStrength(float ambientStrength)
        {
			m_ambientStrength = ambientStrength;
        }

        void OpenGLRenderer::OpenGLRendererImpl::SetSpecularStrength(float specularStrength)
        {
			m_specularStrength = specularStrength;
        }

        void OpenGLRenderer::OpenGLRendererImpl::SetShininess(float shininess)
        {
			m_shininess = shininess;
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

        void OpenGLRenderer::OpenGLRendererImpl::CreateShader(const ShaderOpenGLTypes& shaderType, const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
        {
            std::string vertexShaderSource = Utils::FileOperations::LoadFileAsString(vertexShaderPath);
            std::string fragmentShaderSource = Utils::FileOperations::LoadFileAsString(fragmentShaderPath);
            OpenGLShader* shader = new OpenGLShader(vertexShaderSource, fragmentShaderSource);
            m_shadersMap.insert({ shaderType, shader });
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

        void OpenGLRenderer::OpenGLRendererImpl::CreateColorTexture()
        {
            glGenTextures(1, &m_FBOTexture);
            glBindTexture(GL_TEXTURE_2D, m_FBOTexture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_FBOTexture, 0);
        }

        void OpenGLRenderer::OpenGLRendererImpl::CreateDepthRenderBuffer()
        {
            glGenRenderbuffers(1, &m_depthBuffer);
            glBindRenderbuffer(GL_RENDERBUFFER, m_depthBuffer);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, m_width, m_height);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthBuffer);
        }

        void OpenGLRenderer::OpenGLRendererImpl::SetDrawBuffer()
        {
            GLenum drawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
            glDrawBuffers(1, drawBuffers);
        }

        void OpenGLRenderer::OpenGLRendererImpl::CheckFBOStatus()
        {
            GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
            if (status != GL_FRAMEBUFFER_COMPLETE)
            {
                spdlog::error("Framebuffer incomplete! Status: 0x{:X}", status); // hex
            }
        }

        void OpenGLRenderer::OpenGLRendererImpl::ConfigureFrameBufferTexture()
        {
			GenerateAndBindFrameBuffer();
            CreateColorTexture();
            CreateDepthRenderBuffer();
            SetDrawBuffer();
            CheckFBOStatus();
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

            float aspect = static_cast<float>(m_width) / static_cast<float>(m_height);
            glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);

            glUseProgram(m_shadersMap.at(ShaderOpenGLTypes::RenderableObjects)->GetProgram());

            // Set common uniforms
			m_shadersMap.at(ShaderOpenGLTypes::RenderableObjects)->SetUniform("u_ambientStrength", m_ambientStrength);
			m_shadersMap.at(ShaderOpenGLTypes::RenderableObjects)->SetUniform("u_specularStrength", m_specularStrength);
			m_shadersMap.at(ShaderOpenGLTypes::RenderableObjects)->SetUniform("u_shininess", m_shininess);
            m_shadersMap.at(ShaderOpenGLTypes::RenderableObjects)->SetUniform("u_model", MathUtils::ToGLM(object.GetModelMatrix()));
            m_shadersMap.at(ShaderOpenGLTypes::RenderableObjects)->SetUniform("u_view", MathUtils::ToGLM(m_pCamera->GetViewMatrix()));
            m_shadersMap.at(ShaderOpenGLTypes::RenderableObjects)->SetUniform("u_projection", projectionMatrix);

            // Special case: light sphere
            if (object.IsEmitingLight())
            {
                m_shadersMap.at(ShaderOpenGLTypes::RenderableObjects)->SetUniform("u_lightPos", MathUtils::ToGLM(object.GetCenterPosition()));
                m_shadersMap.at(ShaderOpenGLTypes::RenderableObjects)->SetUniform("u_viewPos", MathUtils::ToGLM(m_pCamera->GetPosition()));
                m_shadersMap.at(ShaderOpenGLTypes::RenderableObjects)->SetUniform("u_lightColor", MathUtils::ToGLM(object.GetColor().ReturnAsVec4()));

                // Force vertex color to white so it appears white
                m_shadersMap.at(ShaderOpenGLTypes::RenderableObjects)->SetUniform("u_vertexColorOverride", MathUtils::ToGLM(object.GetColor().ReturnAsVec4()));
            }
            else
            {
                // Optional: reset override to no-op if your shader expects default value
                m_shadersMap.at(ShaderOpenGLTypes::RenderableObjects)->SetUniform("u_vertexColorOverride", glm::vec4(0.0f));
            }

            glBindVertexArray(object.GetVAO());
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object.GetEBO());
            glDrawElements(GL_TRIANGLES, object.GetIndicesCount(), GL_UNSIGNED_INT, 0);
        }

        void OpenGLRenderer::OpenGLRendererImpl::InitShaders()
        {
            std::string renderableObjectsVertexShaderPath = "shader_program_sources/vertex_shader.glsl";
            std::string renderableObjectsFragmentShaderPath = "shader_program_sources/fragment_shader.glsl";
            std::string gridVertexShaderPath = "shader_program_sources/vertex_shader_grid.glsl";
            std::string gridFragmentShaderPath = "shader_program_sources/fragment_shader_grid.glsl";
			CreateShader(ShaderOpenGLTypes::RenderableObjects, renderableObjectsVertexShaderPath, renderableObjectsFragmentShaderPath);
			CreateShader(ShaderOpenGLTypes::Grid, gridVertexShaderPath, gridFragmentShaderPath);
        }
	}
}
