#include "../include/OpenGLRendererImpl.hpp"
#include "../../Scene/include/SpecialIndices.hpp"
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
			, m_pCamera{ nullptr }
			, m_depthBuffer{ 0 }
			, m_ambientStrength{ 0.1f }
			, m_specularStrength{ 0.5f }
			, m_shininess{ 32.0f }
            , m_isGridVisible{ false }
            , m_attenuationConstant{ 1.0f }
            , m_attenuationLinear{ 0.05f }
            , m_attenuationQuadratic{ 0.001f }
            , m_isIlluminationMode{ false }
        {
            glClearColor(
                BACKGROUND_COLOR_DEFAULT.r,
                BACKGROUND_COLOR_DEFAULT.g,
                BACKGROUND_COLOR_DEFAULT.b,
                BACKGROUND_COLOR_DEFAULT.a
            );
            InitShaders();
            UpdatePerspectiveMatrix(m_width, m_width);
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

        void OpenGLRenderer::OpenGLRendererImpl::RenderFrame(const OpenGLScene& scene) const
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
            RenderObjects(scene);

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

			UpdatePerspectiveMatrix(m_width, m_height);

            glViewport(0, 0, width, height);
            glDeleteFramebuffers(1, &m_FBO);
            glDeleteTextures(1, &m_FBOTexture);
            glDeleteRenderbuffers(1, &m_depthBuffer);

            InitFrameBuffer();
        }

        bool OpenGLRenderer::OpenGLRendererImpl::IsInitialized() const
        {
            return m_isInitialized;
        }

        bool OpenGLRenderer::OpenGLRendererImpl::IsGridVisible() const
        {
            return m_isGridVisible;
        }

        bool OpenGLRenderer::OpenGLRendererImpl::IsIlluminationMode() const
        {
            return m_isIlluminationMode;
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

        float OpenGLRenderer::OpenGLRendererImpl::GetAttenuationConstant() const
        {
            return m_attenuationConstant;
        }

        float OpenGLRenderer::OpenGLRendererImpl::GetAttenuationLinear() const
        {
            return m_attenuationLinear;
        }

        float OpenGLRenderer::OpenGLRendererImpl::GetAttenuationQuadratic() const
        {
            return m_attenuationQuadratic;
        }

        void OpenGLRenderer::OpenGLRendererImpl::SetGridVisible(bool visible)
        {
			m_isGridVisible = visible;
        }

        void OpenGLRenderer::OpenGLRendererImpl::SetIlluminationMode(bool mode)
        {
            m_isIlluminationMode = mode;
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

        void OpenGLRenderer::OpenGLRendererImpl::SetAttenuationConstant(float attenuationConstant)
        {
            m_attenuationConstant = attenuationConstant;
        }

        void OpenGLRenderer::OpenGLRendererImpl::SetAttenuationLinear(float attenuationLinear)
        {
            m_attenuationLinear = attenuationLinear;
        }

        void OpenGLRenderer::OpenGLRendererImpl::SetAttenuationQuadratic(float attenuationQuadratic)
        {
            m_attenuationQuadratic = attenuationQuadratic;
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

        void OpenGLRenderer::OpenGLRendererImpl::RenderObject(const Rendering::IRenderableObjectOpenGL& object) const
        {
            if (m_width == 0 || m_height == 0)
            {
                spdlog::error("Framebuffer dimensions are zero. Cannot render object.");
                return;
            }

            const OpenGLShader& shader = *m_shadersMap.at(ShaderOpenGLTypes::RenderableObjects);

            shader.SetUniform("u_model", MathUtils::ToGLM(object.GetModelMatrix()));
            shader.SetUniform("u_view", MathUtils::ToGLM(m_pCamera->GetViewMatrix()));
            shader.SetUniform("u_projection", m_projectionMatrix);

            glBindVertexArray(object.GetVAO());
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object.GetEBO());
            glDrawElements(GL_TRIANGLES, object.GetIndicesCount(), GL_UNSIGNED_INT, 0);

            shader.UnBind();
        }

        void OpenGLRenderer::OpenGLRendererImpl::RenderObjectWithIllumination(
            const IRenderableObjectOpenGL& object,
            const std::unordered_map<int, Math::Vec3>& lightEmittingObjectCoords,
            const std::unordered_map<int, Math::Vec4>& lightEmittingObjectColors
        ) const
        {
            if (m_width == 0 || m_height == 0)
            {
                spdlog::error("Framebuffer dimensions are zero. Cannot render object.");
                return;
            }

            OpenGLShader& shader = *m_shadersMap.at(ShaderOpenGLTypes::RenderableObjectsIllumination);
            shader.Bind();

            // Set shared uniforms
            shader.SetUniform("u_ambientStrength", m_ambientStrength);
            shader.SetUniform("u_specularStrength", m_specularStrength);
            shader.SetUniform("u_shininess", m_shininess);
            shader.SetUniform("u_model", MathUtils::ToGLM(object.GetModelMatrix()));
            shader.SetUniform("u_view", MathUtils::ToGLM(m_pCamera->GetViewMatrix()));
            shader.SetUniform("u_projection", m_projectionMatrix);
            shader.SetUniform("u_viewPos", MathUtils::ToGLM(m_pCamera->GetPosition()));

            // Attenuation
            shader.SetUniform("u_attenuationConstant", m_attenuationConstant);
            shader.SetUniform("u_attenuationLinear", m_attenuationLinear);
            shader.SetUniform("u_attenuationQuadratic", m_attenuationQuadratic);

            // Convert map values to vectors
            std::vector<glm::vec3> lightPositions;
            std::vector<glm::vec4> lightColors;

            for (const auto& [id, pos] : lightEmittingObjectCoords)
            {
                auto colorIt = lightEmittingObjectColors.find(id);
                if (colorIt != lightEmittingObjectColors.end())
                {
                    lightPositions.push_back(MathUtils::ToGLM(pos));
                    lightColors.push_back(MathUtils::ToGLM(colorIt->second));
                }
                else
                {
                    spdlog::warn("Light position with ID {} has no corresponding color. Skipping.", id);
                }
            }

            // Send light data to shader
            shader.SetUniform("u_numLights", static_cast<int>(lightPositions.size()));
            shader.SetUniform("u_lightPos", lightPositions);
            shader.SetUniform("u_lightColor", lightColors);

            // Vertex color override
            if (object.IsEmitingLight())
            {
                shader.SetUniform("u_vertexColorOverride", MathUtils::ToGLM(object.GetColor().ReturnAsVec4()));
            }
            else
            {
                shader.SetUniform("u_vertexColorOverride", glm::vec4(0.0f));
            }

            // Draw
            glBindVertexArray(object.GetVAO());
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object.GetEBO());
            glDrawElements(GL_TRIANGLES, object.GetIndicesCount(), GL_UNSIGNED_INT, 0);
            shader.UnBind();
        }

        void OpenGLRenderer::OpenGLRendererImpl::RenderObjects(const OpenGLScene& scene) const
        {
            for (const auto& [id, object] : scene.GetObjects())
            {
                if (id == static_cast<int>(SpecialIndices::Grid))
                {
                    if (!m_isGridVisible)
                        continue;

                    RenderGrid(*object);
                }
                else
                {
                    if (m_isIlluminationMode)
                    {
                        RenderObjectWithIllumination(
                            *object,
                            scene.GetLightEmittingObjectsCoords(), 
                            scene.GetLightEmittingObjectsColors()
                        );
                    }
                    else
                    {
                        RenderObject(*object);
                    }
                }
            }
        }

        void OpenGLRenderer::OpenGLRendererImpl::RenderGrid(const IRenderableObjectOpenGL& object) const
        {
            if (m_width == 0 || m_height == 0)
            {
                spdlog::error("Framebuffer dimensions are zero. Cannot render object.");
                return;
            }

            const OpenGLShader& shader = *m_shadersMap.at(ShaderOpenGLTypes::Grid);
            shader.Bind();

            glm::mat4 viewMatrix = MathUtils::ToGLM(m_pCamera->GetViewMatrix());

            shader.SetUniform("u_view", viewMatrix);
            shader.SetUniform("u_projection", m_projectionMatrix);

            glBindVertexArray(object.GetVAO());
            glBindBuffer(GL_ARRAY_BUFFER, object.GetVBO());

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object.GetEBO());
            glDrawElements(GL_LINES, object.GetIndicesCount(), GL_UNSIGNED_INT, 0);

            shader.UnBind();
        }

        void OpenGLRenderer::OpenGLRendererImpl::InitShaders()
        {
            std::vector<ShaderDefinition> shaders = {
                {
                    ShaderOpenGLTypes::RenderableObjects,
                    "shader_program_sources/vertex_shader.glsl",
                    "shader_program_sources/fragment_shader.glsl"
                },
                {
                    ShaderOpenGLTypes::RenderableObjectsIllumination,
                    "shader_program_sources/vertex_shader_illumination.glsl",
                    "shader_program_sources/fragment_shader_illumination.glsl"
                },
                {
                    ShaderOpenGLTypes::Grid,
                    "shader_program_sources/vertex_shader_grid.glsl",
                    "shader_program_sources/fragment_shader_grid.glsl" 
                }
            };

            for (const auto& shader : shaders)
            {
                CreateShader(shader.type, shader.vertexPath, shader.fragmentPath);
            }
        }

        void OpenGLRenderer::OpenGLRendererImpl::UpdatePerspectiveMatrix(int width, int height)
        {
            float aspect = static_cast<float>(m_width) / static_cast<float>(m_height);
            m_projectionMatrix = glm::infinitePerspective(glm::radians(45.0f), aspect, 0.1f);
        }
	}
}
