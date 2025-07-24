#include "../include/OpenGLRendererImpl.hpp"
#include "../../Scene/include/SpecialIndices.hpp"
#include "../../Utils/include/MathUtils.hpp"
#include "../../Light/include/LuminousBehavior.hpp"
#include "../../Light/include/NonLuminousBehavior.hpp"
#include "../../Light/include/LightData.hpp"
#include "../../RenderableObjects/include/GridOpenGL.hpp"
#include "../../Light/include/PointLight.hpp"
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
            , m_lightSpace{ glm::mat4(1.0f) }
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

        void OpenGLRenderer::OpenGLRendererImpl::Init(int width, int height, bool illuminationMode)
        {
            if (width <= 0 or height <= 0)
            {
				spdlog::error("Invalid dimensions for initialization: {}x{}", width, height);
                return;
            }

			m_width = width;
			m_height = height;
            m_isIlluminationMode = illuminationMode;

            if (m_isIlluminationMode)
            {
                InitFrameBuffer();
                InitShadowMap(width, height);
            }
            
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

        void OpenGLRenderer::OpenGLRendererImpl::RenderFrame(OpenGLScene& scene)
        {
            if (!m_isInitialized)
                return;

			BeginFrame();

            if (m_isIlluminationMode)
            {
                glm::mat4 lightSpace = ComputeLightSpaceMatrix(scene);

                ShadowMapDepthPass(scene, lightSpace);
                RenderNonLuminousObjects(scene, lightSpace);
                RenderLuminousObjects(scene);
            }
            else
            {
				RenderObjects(scene);
            }

            EndFrame();
			LogFPS();
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
                switch (status)
                {
                    case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT: spdlog::error("Incomplete attachment"); break;
                    case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT: spdlog::error("Missing attachment"); break;
                    case GL_FRAMEBUFFER_UNSUPPORTED: spdlog::error("Unsupported framebuffer format"); break;
                }
            }
        }

        void OpenGLRenderer::OpenGLRendererImpl::ConfigureFrameBufferTexture()
        {
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
			EnableFaceCulling(GL_FRONT, GL_CCW); // Enable front-face culling with counter-clockwise winding
            if (m_width <= 0 || m_height <= 0)
            {
                spdlog::error("Shadow map dimensions are zero. Cannot render shadow map.");
                return;
			}

            int prevFBO;
            glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &prevFBO);

            glBindFramebuffer(GL_FRAMEBUFFER, m_shadowFBO);
            glViewport(0, 0, m_width, m_height);
            glEnable(GL_DEPTH_TEST);
            glClear(GL_DEPTH_BUFFER_BIT);

            // Cull FRONT faces to reduce shadow acne
			EnableFaceCulling(GL_FRONT, GL_CW);

            // Use polygon offset to prevent z-fighting
            glEnable(GL_POLYGON_OFFSET_FILL);
            glPolygonOffset(2.0f, 4.0f); // Adjust if needed

            OpenGLShader& depthShader = *m_shadersMap.at(ShaderOpenGLTypes::ShadowMap);
            depthShader.Bind();
            depthShader.SetUniform("u_lightSpaceMatrix", lightSpace);

            for (auto& [id, obj] : scene.GetObjects())
            {
                depthShader.SetUniform("u_model", MathUtils::ToGLM(obj->GetModelMatrix()));
                glBindVertexArray(obj->GetVAO());
                glDrawElements(GL_TRIANGLES, obj->GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
            }

            depthShader.UnBind();
            glBindFramebuffer(GL_FRAMEBUFFER, prevFBO);
			DisableFaceCulling(); // Reset face culling state
        }

        void OpenGLRenderer::OpenGLRendererImpl::RenderNonLuminousObjects(const OpenGLScene& scene, const glm::mat4& lightSpace) const
        {
			EnableFaceCulling(GL_BACK, GL_CCW); // Enable back-face culling with counter-clockwise winding
            // bind the shadow map into texture unit 5
            const int SHADOW_UNIT = 5;
            glActiveTexture(GL_TEXTURE0 + SHADOW_UNIT);
            glBindTexture(GL_TEXTURE_2D, m_shadowMapTexture);

            OpenGLShader& nlShader = *m_shadersMap.at(ShaderOpenGLTypes::RenderableObjectsNonLuminous);
            nlShader.Bind();

            // Camera and shadow uniforms
            nlShader.SetUniform("u_view", MathUtils::ToGLM(m_pCamera->GetViewMatrix()));
            nlShader.SetUniform("u_projection", m_projectionMatrix);
            nlShader.SetUniform("u_viewPos", MathUtils::ToGLM(m_pCamera->GetPosition()));
            nlShader.SetUniform("u_lightSpaceMatrix", lightSpace);
            nlShader.SetUniform("u_shadowMap", SHADOW_UNIT);

            PopulateLightUniforms(nlShader, scene);
            RenderEachNonLuminousObject(nlShader, scene);

            nlShader.UnBind();

			DisableFaceCulling(); // Reset face culling state
        }

        void OpenGLRenderer::OpenGLRendererImpl::RenderLuminousObjects(const OpenGLScene& scene) const
        {
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
			DisableFaceCulling();
        }

        void OpenGLRenderer::OpenGLRendererImpl::RenderObjects(const OpenGLScene& scene) const
        {
            glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
            glViewport(0, 0, m_width, m_height);
            glEnable(GL_DEPTH_TEST);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			EnableFaceCulling(GL_BACK, GL_CCW); // Enable back-face culling with counter-clockwise winding

            OpenGLShader& shader = *m_shadersMap.at(ShaderOpenGLTypes::RenderableObjects);
            shader.Bind();
            shader.SetUniform("u_view", MathUtils::ToGLM(m_pCamera->GetViewMatrix()));
            shader.SetUniform("u_projection", m_projectionMatrix);

            for (auto& [id, obj] : scene.GetObjects())
            {
                if (id >= 0)
                {
                    shader.SetUniform("u_model", MathUtils::ToGLM(obj->GetModelMatrix()));
                    glBindVertexArray(obj->GetVAO());
                    glDrawElements(
                        GL_TRIANGLES,
                        obj->GetIndicesCount(),
                        GL_UNSIGNED_INT,
                        nullptr
                    );
                }
            }
            shader.UnBind();

			DisableFaceCulling(); // Reset face culling state
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

        void OpenGLRenderer::OpenGLRendererImpl::BeginFrame() const
        {
            glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
            glViewport(0, 0, m_width, m_height);
            glEnable(GL_DEPTH_TEST);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        void OpenGLRenderer::OpenGLRendererImpl::EndFrame() const
        {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            glViewport(0, 0, m_width, m_height);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        void OpenGLRenderer::OpenGLRendererImpl::LogFPS() const
        {
            std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
            float duration = std::chrono::duration<float>(now - m_lastFrameTime).count();
            m_lastFrameTime = now;

            if (duration > 0.0f)
            {
                float fps = 1.0f / duration;
                spdlog::info("FPS: {:.2f}", fps);
            }
        }

        void OpenGLRenderer::OpenGLRendererImpl::EnableFaceCulling(unsigned int face, unsigned int winding) const
        {
            glEnable(GL_CULL_FACE);
            glCullFace(face);
			glFrontFace(winding);
        }

        void OpenGLRenderer::OpenGLRendererImpl::DisableFaceCulling() const
        {
            glDisable(GL_CULL_FACE);
			glFrontFace(GL_CCW); // Reset to default counter-clockwise winding
        }

        void OpenGLRenderer::OpenGLRendererImpl::PrepareFramebufferForNonLuminousPass() const
        {
            glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
            glViewport(0, 0, m_width, m_height);
            glEnable(GL_DEPTH_TEST);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        void OpenGLRenderer::OpenGLRendererImpl::BindShadowMap(int textureUnit) const
        {
            glActiveTexture(GL_TEXTURE0 + textureUnit);
            glBindTexture(GL_TEXTURE_2D, m_shadowMapTexture);
        }

        void OpenGLRenderer::OpenGLRendererImpl::RenderGridIfVisible(const OpenGLScene& scene) const
        {
            if (m_isGridVisible)
            {
                const auto& objects = scene.GetObjects();
                auto it = objects.find(static_cast<int>(SpecialIndices::Grid));
                if (it != objects.end())
                {
                    RenderGrid(*it->second);
                }
            }
        }

        void OpenGLRenderer::OpenGLRendererImpl::PopulateLightUniforms(OpenGLShader& shader, const OpenGLScene& scene) const
        {
            const auto& luminousObjsMap = scene.GetLuminousObjects();

            std::vector<float> lightConstants, lightLinears, lightQuadratics;
            std::vector<glm::vec3> lightPositions, lightAmbientValues, lightDiffuseValues, lightSpecularValues;

            for (const auto& [id, lightCaster] : luminousObjsMap)
            {
                glm::vec3 lightPosGLM = MathUtils::ToGLM(lightCaster->GetCenterPosition());
                lightPositions.push_back(lightPosGLM);

                auto* luminousBehavior = dynamic_cast<LuminousBehavior*>(lightCaster->GetLightBehavior());
                auto* pointLight = dynamic_cast<PointLight*>(luminousBehavior->GetLight());

                lightConstants.push_back(pointLight->GetAttenuationConstant());
                lightLinears.push_back(pointLight->GetAttenuationLinear());
                lightQuadratics.push_back(pointLight->GetAttenuationQuadratic());

                lightAmbientValues.push_back({ 0.9f, 0.9f, 0.9f }); // or get from config
                lightDiffuseValues.push_back(pointLight->GetDiffuse());
                lightSpecularValues.push_back(pointLight->GetSpecular());
            }

            shader.SetUniform("u_numLights", static_cast<int>(lightPositions.size()));
            shader.SetUniform("u_positionLight", lightPositions);
            shader.SetUniform("u_constantLight", lightConstants);
            shader.SetUniform("u_linearLight", lightLinears);
            shader.SetUniform("u_quadraticLight", lightQuadratics);
            shader.SetUniform("u_ambientLight", lightAmbientValues);
            shader.SetUniform("u_diffuseLight", lightDiffuseValues);
            shader.SetUniform("u_specularLight", lightSpecularValues);
        }

        void OpenGLRenderer::OpenGLRendererImpl::RenderEachNonLuminousObject(OpenGLShader& shader, const OpenGLScene& scene) const
        {
            for (const auto& [id, obj] : scene.GetObjects())
            {
                if (id < 0 || obj->IsLuminous())
                    continue;

                auto* nonLum = dynamic_cast<NonLuminousBehavior*>(obj->GetLightBehavior());
                if (!nonLum)
                    continue;

                Material material = nonLum->GetMaterial();
                glm::mat3 normalMatrix = glm::inverseTranspose(glm::mat3(MathUtils::ToGLM(obj->GetModelMatrix())));

                shader.SetUniform("u_ambientMaterial", MathUtils::ToGLM(material.GetAmbient()));
                shader.SetUniform("u_diffuseMaterial", MathUtils::ToGLM(material.GetDiffuse()));
                shader.SetUniform("u_specularMaterial", MathUtils::ToGLM(material.GetSpecular()));
                shader.SetUniform("u_shininessMaterial", material.GetShininess());
                shader.SetUniform("u_model", MathUtils::ToGLM(obj->GetModelMatrix()));
                shader.SetUniform("u_normalMatrix", normalMatrix);

                glBindVertexArray(obj->GetVAO());
                glDrawElements(GL_TRIANGLES, obj->GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
            }
        }
        glm::mat4 OpenGLRenderer::OpenGLRendererImpl::ComputeLightSpaceMatrix(const OpenGLScene& scene) const
        {
            // 1) Grab the first light's world-space position:
            std::unordered_map<int, Math::Vec3> lightCoords;
            const std::unordered_map<int, IRenderableObjectOpenGL*>& luminousObjsMap = scene.GetLuminousObjects();
            lightCoords.reserve(luminousObjsMap.size());

            for (const auto& [id, lightCaster] : luminousObjsMap)
            {
                lightCoords[id] = lightCaster->GetCenterPosition();
            }

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
            float orthoHalfSize = 10.0f;
            float nearPlane = 1.0f; // TODO: make near plane the radius or half extent of the sphere or the cube
            float farPlane = 30.0f;
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
