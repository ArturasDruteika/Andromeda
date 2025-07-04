#include "../include/OpenGLRendererImpl.hpp"
#include "../../Scene/include/SpecialIndices.hpp"
#include "../../Utils/include/MathUtils.hpp"
#include "../../Light/include/LuminousBehavior.hpp"
#include "../../Light/include/NonLuminousBehavior.hpp"
#include "../../Light/include/LightData.hpp"
#include "../../RenderableObjects/include/GridOpenGL.hpp"
#include "FileOperations.hpp"
#include "Colors.hpp"
#include "glad/gl.h"
#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>


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
			, m_RBO{ 0 }
            , m_shadowMapTexture{ 0 }
            , m_isGridVisible{ false }
            , m_isIlluminationMode{ false }
            , m_shadowFBO{ 0 }
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
            InitShadowMap(width, height);

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
            glDeleteRenderbuffers(1, &m_RBO);
            m_isInitialized = false;
        }

        void OpenGLRenderer::OpenGLRendererImpl::RenderFrame(const OpenGLScene& scene) const
        {
            if (!m_isInitialized)
                return;

            glm::mat4 lightSpace = ComputeLightSpaceMatrix(scene);

			ShadowMapDepthPass(scene, lightSpace);
			RenderNonLuminousObjects(scene, lightSpace);
			RenderLuminousObjects(scene);

            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }


        void OpenGLRenderer::OpenGLRendererImpl::Resize(int width, int height)
        {
            if (width <= 0 || height <= 0)
            {
                spdlog::error("Invalid dimensions for resizing: {}x{}", width, height);
                return;
            }
            if (width == m_width && height == m_height)
            {
                spdlog::warn("Resize called with same dimensions: {}x{}", width, height);
                return;
            }

            // Unbind any bound framebuffers/textures
            glBindFramebuffer(GL_FRAMEBUFFER, 0);

            // Delete existing framebuffer resources
            glDeleteFramebuffers(1, &m_FBO);
            glDeleteTextures(1, &m_FBOTexture);
            glDeleteRenderbuffers(1, &m_RBO);

            // Delete shadow map resources
            glDeleteFramebuffers(1, &m_shadowFBO);
            glDeleteTextures(1, &m_shadowMapTexture);

            // Update dimensions
            m_width = width;
            m_height = height;

            // Recompute projection
            UpdatePerspectiveMatrix(m_width, m_height);
            glViewport(0, 0, width, height);

            // Recreate buffers
            InitFrameBuffer();
            InitShadowMap(width, height);
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

        unsigned int OpenGLRenderer::OpenGLRendererImpl::GetDepthRenderBuffer() const
        {
            return m_RBO;
        }

        unsigned int OpenGLRenderer::OpenGLRendererImpl::GetShadowMap() const
        {
            return m_shadowMapTexture;
        }

        int OpenGLRenderer::OpenGLRendererImpl::GetWidth() const
        {
            return m_width;
        }

        int OpenGLRenderer::OpenGLRendererImpl::GetHeight() const
        {
            return m_height;
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

        void OpenGLRenderer::OpenGLRendererImpl::InitFrameBuffer()
        {
            if (m_width <= 0 or m_height <= 0)
            {
                spdlog::warn("Cannot initialize framebuffer with dimensions: {}x{}", m_width, m_height);
                return;
            }
			GenerateAndBindFrameBuffer();
            CreateColorTexture();
			ConfigureFrameBufferTexture();
			UnbindFrameBuffer();
            m_isInitialized = true;
        }

        void OpenGLRenderer::OpenGLRendererImpl::InitShadowMap(int width, int height)
        {
            // 1) Create the FBO
            glGenFramebuffers(1, &m_shadowFBO);
            glBindFramebuffer(GL_FRAMEBUFFER, m_shadowFBO);

            // 2) Create & configure the depth texture
            glGenTextures(1, &m_shadowMapTexture);
            glBindTexture(GL_TEXTURE_2D, m_shadowMapTexture);
            glTexImage2D(GL_TEXTURE_2D,
                0,
                GL_DEPTH_COMPONENT24,
                width,
                height,
                0,
                GL_DEPTH_COMPONENT,
                GL_FLOAT,
                nullptr);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
            float borderColor[] = { 1, 1, 1, 1 };
            glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

            // 3) Attach it as the depth-only attachment
            glFramebufferTexture2D(GL_FRAMEBUFFER,
                GL_DEPTH_ATTACHMENT,
                GL_TEXTURE_2D,
                m_shadowMapTexture,
                0);

            // 4) No color writes for this FBO
            glDrawBuffer(GL_NONE);
            glReadBuffer(GL_NONE);

            // 5) Check completeness
            if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
                spdlog::error("Shadow FBO not complete! Status: 0x{:X}", glCheckFramebufferStatus(GL_FRAMEBUFFER));

            // 6) Unbind so we don't accidentally render to it
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
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

        void OpenGLRenderer::OpenGLRendererImpl::CreateColorTexture()
        {
            glGenTextures(1, &m_FBOTexture);
            glBindTexture(GL_TEXTURE_2D, m_FBOTexture);
            glTexImage2D(
                GL_TEXTURE_2D, 
                0, 
                GL_RGBA, 
                m_width, 
                m_height, 
                0, 
                GL_RGBA, 
                GL_UNSIGNED_BYTE, 
                nullptr
            );
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_FBOTexture, 0);
        }

        void OpenGLRenderer::OpenGLRendererImpl::CreateRenderBuffer()
        {
            glGenRenderbuffers(1, &m_RBO);
            glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, m_width, m_height);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_RBO);
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
            CreateRenderBuffer();
            SetDrawBuffer();
            CheckFBOStatus();
        }

        void OpenGLRenderer::OpenGLRendererImpl::UnbindFrameBuffer() const
        {
            // Unbind the framebuffer
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        void OpenGLRenderer::OpenGLRendererImpl::ShadowMapDepthPass(const OpenGLScene& scene, const glm::mat4& lightSpace) const
        {
            // ----- PASS A: Shadow-map depth pass -----
            glBindFramebuffer(GL_FRAMEBUFFER, m_shadowFBO);
            glViewport(0, 0, m_width, m_height);
            glEnable(GL_DEPTH_TEST);
            glClear(GL_DEPTH_BUFFER_BIT);

            OpenGLShader& depthShader = *m_shadersMap.at(ShaderOpenGLTypes::ShadowMap);
            depthShader.Bind();
            depthShader.SetUniform("u_lightSpaceMatrix", lightSpace);

            for (auto& [id, obj] : scene.GetObjects())
            {
                depthShader.SetUniform("u_model", MathUtils::ToGLM(obj->GetModelMatrix()));
                glBindVertexArray(obj->GetVAO());
                glDrawElements(GL_TRIANGLES,
                    obj->GetIndicesCount(),
                    GL_UNSIGNED_INT,
                    nullptr);
            }
            depthShader.UnBind();
        }

        void OpenGLRenderer::OpenGLRendererImpl::RenderNonLuminousObjects(const OpenGLScene& scene, const glm::mat4& lightSpace) const
        {
            // ----- PASS B: Lighting + shadows -----
            glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
            glViewport(0, 0, m_width, m_height);
            glEnable(GL_DEPTH_TEST);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // bind the shadow map into texture unit 5
            const int SHADOW_UNIT = 5;
            glActiveTexture(GL_TEXTURE0 + SHADOW_UNIT);
            glBindTexture(GL_TEXTURE_2D, m_shadowMapTexture);

            if (m_isGridVisible)
                RenderGrid(*scene.GetObjects().at(static_cast<int>(SpecialIndices::Grid)));

            // --- (a) Non-luminous objects: Blinn-Phong + shadows ---
            OpenGLShader& nlShader = *m_shadersMap.at(ShaderOpenGLTypes::RenderableObjectsNonLuminous);
            nlShader.Bind();

            // camera uniforms
            nlShader.SetUniform("u_view", MathUtils::ToGLM(m_pCamera->GetViewMatrix()));
            nlShader.SetUniform("u_projection", m_projectionMatrix);
            nlShader.SetUniform("u_viewPos", MathUtils::ToGLM(m_pCamera->GetPosition()));

            // shadow uniforms
            nlShader.SetUniform("u_lightSpaceMatrix", lightSpace);
            nlShader.SetUniform("u_shadowMap", SHADOW_UNIT);

            // material ambient global
            nlShader.SetUniform("u_ambientStrength", scene.GetAmbientStrength());

            // collect all lights
            const std::unordered_map<int, Math::Vec3>& coords = scene.GetLightEmittingObjectsCoords();
            const std::unordered_map<int, Math::Vec4>& colors = scene.GetLightEmittingObjectsColors();
            const std::unordered_map<int, LuminousBehavior*>& behaviors = scene.GetLuminousObjectsBehaviors();

            std::vector<glm::vec3> lightPositions;
            std::vector<glm::vec4> lightColors;
            std::vector<float> lightConstants;
            std::vector<float> lightLinears;
            std::vector<float> lightQuadratics;

            lightPositions.reserve(coords.size());
            lightColors.reserve(coords.size());
            lightConstants.reserve(coords.size());
            lightLinears.reserve(coords.size());
            lightQuadratics.reserve(coords.size());

            for (auto& [id, pos] : coords)
            {
                glm::vec3 lightPosGLM = MathUtils::ToGLM(pos);
                lightPositions.push_back(lightPosGLM);
                lightColors.push_back(MathUtils::ToGLM(colors.at(id)));

                LuminousBehavior* lumBehavior = behaviors.at(id);
                LightData data = lumBehavior->GetLightData();
                lightConstants.push_back(data.GetAttenuationConstant());
                lightLinears.push_back(data.GetAttenuationLinear());
                lightQuadratics.push_back(data.GetAttenuationQuadratic());
            }

            int numLights = static_cast<int>(lightPositions.size());
            nlShader.SetUniform("u_numLights", numLights);
            nlShader.SetUniform("u_lightPos", lightPositions);
            nlShader.SetUniform("u_lightColor", lightColors);
            nlShader.SetUniform("u_lightConstant", lightConstants);
            nlShader.SetUniform("u_lightLinear", lightLinears);
            nlShader.SetUniform("u_lightQuadratic", lightQuadratics);

            // draw each non-luminous object with its own material
            for (auto& [id, obj] : scene.GetObjects())
            {
                if (id >= 0)
                {
                    if (!obj->IsLuminous())
                    {
                        glm::mat3 normalMatrix = glm::inverseTranspose(glm::mat3(MathUtils::ToGLM(obj->GetModelMatrix())));
                        // per-object material uniforms
                        NonLuminousBehavior* nonLum = dynamic_cast<NonLuminousBehavior*>(obj->GetLightBehavior());
                        nlShader.SetUniform("u_ambientReflectivity", nonLum->GetAmbientReflectivity());
                        nlShader.SetUniform("u_diffuseStrength", nonLum->GetDiffuseStrength());
                        nlShader.SetUniform("u_specularStrength", nonLum->GetSpecularStrength());
                        nlShader.SetUniform("u_shininess", nonLum->GetShininess());
                        nlShader.SetUniform("u_model", MathUtils::ToGLM(obj->GetModelMatrix()));
                        nlShader.SetUniform("u_normalMatrix", normalMatrix);
                        glBindVertexArray(obj->GetVAO());
                        glDrawElements(
                            GL_TRIANGLES,
                            obj->GetIndicesCount(),
                            GL_UNSIGNED_INT,
                            nullptr
                        );
                    }
                }
            }
            nlShader.UnBind();
        }

        void OpenGLRenderer::OpenGLRendererImpl::RenderLuminousObjects(const OpenGLScene& scene) const
        {
            // --- (b) Luminous objects: unshaded pass-through ---
            OpenGLShader& lumShader = *m_shadersMap.at(ShaderOpenGLTypes::RenderableObjectsLuminous);
            lumShader.Bind();
            lumShader.SetUniform("u_view", MathUtils::ToGLM(m_pCamera->GetViewMatrix()));
            lumShader.SetUniform("u_projection", m_projectionMatrix);

            for (auto& [id, obj] : scene.GetObjects())
            {
                if (obj->IsLuminous())
                {
                    lumShader.SetUniform("u_model", MathUtils::ToGLM(obj->GetModelMatrix()));
                    glBindVertexArray(obj->GetVAO());
                    glDrawElements(
                        GL_TRIANGLES,
                        obj->GetIndicesCount(),
                        GL_UNSIGNED_INT,
                        nullptr
                    );
                }
            }
            lumShader.UnBind();
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
                    "shader_program_sources/vertex.glsl",
                    "shader_program_sources/fragment.glsl"
                },
                {
                    ShaderOpenGLTypes::Grid,
                    "shader_program_sources/vertex_grid.glsl",
                    "shader_program_sources/fragment_grid.glsl" 
                },
                {
                    ShaderOpenGLTypes::RenderableObjectsLuminous,
                    "shader_program_sources/vertex_illumination.glsl",
                    "shader_program_sources/fragment_luminous_objects.glsl"
                },
                {
                    ShaderOpenGLTypes::RenderableObjectsNonLuminous,
                    "shader_program_sources/vertex_illumination.glsl",
                    "shader_program_sources/fragment_non_luminous_objects.glsl"
                },
                {
                    ShaderOpenGLTypes::ShadowMap,
                    "shader_program_sources/vertex_depth_only.glsl",
                    "shader_program_sources/fragment_depth_only.glsl"
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

        glm::mat4 OpenGLRenderer::OpenGLRendererImpl::ComputeLightSpaceMatrix(const OpenGLScene& scene) const
        {
            // 1) Grab the first light's world-space position:
            const std::unordered_map<int, Math::Vec3>& lightCoords = scene.GetLightEmittingObjectsCoords();
            if (lightCoords.empty())
                return glm::mat4(1.0f);

            // use the first entry in the map:
            glm::vec3 lightPos = MathUtils::ToGLM(lightCoords.begin()->second);

            // 2) Define a simple scene-center and up vector:
            //    (You may want to compute an actual scene bounding-box center here.)
            glm::vec3 sceneCenter(0.0f);
            glm::vec3 up(0.0f, 1.0f, 0.0f);

            // 3) Build a view matrix "from the light" looking at the scene center:
            glm::mat4 lightView = glm::lookAt(lightPos, sceneCenter, up);

            // 4) Build an orthographic projection for the directional light.
            //    Tweak these extents and near/far to cover your scene.
            float orthoHalfSize = 20.0f;
            float nearPlane = 1.0f;
            float farPlane = 100.0f;
            glm::mat4 lightProj = glm::ortho(
                -orthoHalfSize, orthoHalfSize,
                -orthoHalfSize, orthoHalfSize,
                nearPlane, farPlane
            );

            // 5) Combine: world -> light-clip -> light-NDC
            return lightProj * lightView;
        }
	}
}
