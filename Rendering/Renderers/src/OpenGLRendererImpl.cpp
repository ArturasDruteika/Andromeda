#include "../include/OpenGLRendererImpl.hpp"
#include "../../Scene/include/SpecialIndices.hpp"
#include "../../Utils/include/MathUtils.hpp"
#include "../../Light/include/LuminousBehavior.hpp"
#include "../../Light/include/NonLuminousBehavior.hpp"
#include "../../Light/include/LightData.hpp"
#include "../../RenderableObjects/include/GridOpenGL.hpp"
#include "../../Light/include/PointLight.hpp"
#include "../../Shaders/include/OpenGLShader.hpp"
#include "../../Shaders/include/ShaderOpenGLTypes.hpp"
#include "../../RenderableObjects/include/IRenderableObjectOpenGL.hpp"
#include "FileOperations.hpp"
#include "Colors.hpp"
#include "glad/gl.h"
#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>


namespace Andromeda::Rendering
{
    constexpr Space::Color BACKGROUND_COLOR_DEFAULT{ 0.0f, 0.0f, 0.0f, 1.0f };

    OpenGLRenderer::OpenGLRendererImpl::OpenGLRendererImpl()
        : m_isInitialized{ false }
        , m_width{ 0 }
        , m_height{ 0 }
        , m_pCamera{ nullptr }
        , m_isGridVisible{ false }
        , m_isIlluminationMode{ false }
        , m_lightSpace{ glm::mat4(1.0f) }
        , m_pShaderManager{ nullptr }
    {
        glClearColor(
            BACKGROUND_COLOR_DEFAULT.r,
            BACKGROUND_COLOR_DEFAULT.g,
            BACKGROUND_COLOR_DEFAULT.b,
            BACKGROUND_COLOR_DEFAULT.a
        );
        m_pShaderManager = new ShaderManager(true);
        UpdatePerspectiveMatrix(m_width, m_height);
    }

    OpenGLRenderer::OpenGLRendererImpl::~OpenGLRendererImpl()
    {
        DeInit();
    }

    void OpenGLRenderer::OpenGLRendererImpl::Init(int width, int height, bool illuminationMode)
    {
        if (width <= 0 || height <= 0)
        {
            spdlog::error("Invalid dimensions for initialization: {}x{}", width, height);
            return;
        }

        m_width = width;
        m_height = height;
        m_isIlluminationMode = illuminationMode;

        // main color+depth framebuffer
        if (!m_mainFBO.Init(width, height, FrameBufferType::ColorDepth))
        {
            spdlog::error("Failed to create main framebuffer");
            return;
        }

        // depth-only shadow map
        if (m_isIlluminationMode)
        {
            if (!m_shadowFBO.Init(width, height, FrameBufferType::Depth))
            {
                spdlog::error("Failed to create shadow framebuffer");
                return;
            }
        }

        UpdatePerspectiveMatrix(width, height);
        m_isInitialized = true;
    }

    void OpenGLRenderer::OpenGLRendererImpl::DeInit()
    {
        delete m_pShaderManager;
        m_pShaderManager = nullptr;
        m_isInitialized = false;
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

        m_width = width;
        m_height = height;
        glViewport(0, 0, width, height);
        UpdatePerspectiveMatrix(width, height);

        m_mainFBO.Resize(width, height);
        if (m_isIlluminationMode)
            m_shadowFBO.Resize(width, height);
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
        return m_mainFBO.GetId();
    }

    unsigned int OpenGLRenderer::OpenGLRendererImpl::GetFrameBufferObjectTexture() const
    {
        return m_mainFBO.GetColorTexture();
    }

    unsigned int OpenGLRenderer::OpenGLRendererImpl::GetDepthRenderBuffer() const
    {
        return m_mainFBO.GetDepthRenderbuffer();
    }

    unsigned int OpenGLRenderer::OpenGLRendererImpl::GetShadowMap() const
    {
        return m_shadowFBO.GetDepthTexture();
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

    void OpenGLRenderer::OpenGLRendererImpl::ShadowMapDepthPass(const OpenGLScene& scene, const glm::mat4& lightSpace) const
    {
        EnableFaceCulling(GL_FRONT, GL_CCW);

        if (m_width <= 0 || m_height <= 0)
        {
            spdlog::error("Shadow map dimensions are zero. Cannot render shadow map.");
            return;
        }

        int prevFBO;
        glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &prevFBO);

        m_shadowFBO.Bind();
        glViewport(0, 0, m_width, m_height);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_DEPTH_BUFFER_BIT);

        EnableFaceCulling(GL_FRONT, GL_CW);

        glEnable(GL_POLYGON_OFFSET_FILL);
        glPolygonOffset(2.0f, 4.0f);

        OpenGLShader* depthShader = m_pShaderManager->GetShader(ShaderOpenGLTypes::ShadowMap);
        depthShader->Bind();
        depthShader->SetUniform("u_lightSpaceMatrix", lightSpace);

        for (auto& [id, obj] : scene.GetObjects())
        {
            depthShader->SetUniform("u_model", MathUtils::ToGLM(obj->GetModelMatrix()));
            glBindVertexArray(obj->GetVAO());
            glDrawElements(GL_TRIANGLES, obj->GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
        }

        depthShader->UnBind();

        glBindFramebuffer(GL_FRAMEBUFFER, prevFBO);
        DisableFaceCulling();
    }

    void OpenGLRenderer::OpenGLRendererImpl::RenderNonLuminousObjects(const OpenGLScene& scene, const glm::mat4& lightSpace) const
    {
        EnableFaceCulling(GL_BACK, GL_CCW);
        const int SHADOW_UNIT = 5;
        glActiveTexture(GL_TEXTURE0 + SHADOW_UNIT);
        glBindTexture(GL_TEXTURE_2D, m_shadowFBO.GetDepthTexture());

        OpenGLShader* nlShader = m_pShaderManager->GetShader(ShaderOpenGLTypes::RenderableObjectsNonLuminous);
        nlShader->Bind();

        nlShader->SetUniform("u_view", MathUtils::ToGLM(m_pCamera->GetViewMatrix()));
        nlShader->SetUniform("u_projection", m_projectionMatrix);
        nlShader->SetUniform("u_viewPos", MathUtils::ToGLM(m_pCamera->GetPosition()));
        nlShader->SetUniform("u_lightSpaceMatrix", lightSpace);
        nlShader->SetUniform("u_shadowMap", SHADOW_UNIT);

        PopulateLightUniforms(*nlShader, scene);
        RenderEachNonLuminousObject(*nlShader, scene);

        nlShader->UnBind();
        DisableFaceCulling();
    }

    void OpenGLRenderer::OpenGLRendererImpl::RenderLuminousObjects(const OpenGLScene& scene) const
    {
        OpenGLShader* lumShader = m_pShaderManager->GetShader(ShaderOpenGLTypes::RenderableObjectsLuminous);
        lumShader->Bind();
        lumShader->SetUniform("u_view", MathUtils::ToGLM(m_pCamera->GetViewMatrix()));
        lumShader->SetUniform("u_projection", m_projectionMatrix);

        for (auto& [id, obj] : scene.GetObjects())
        {
            if (obj->IsLuminous())
            {
                lumShader->SetUniform("u_model", MathUtils::ToGLM(obj->GetModelMatrix()));
                glBindVertexArray(obj->GetVAO());
                glDrawElements(GL_TRIANGLES, obj->GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
            }
        }
        lumShader->UnBind();
        DisableFaceCulling();
    }

    void OpenGLRenderer::OpenGLRendererImpl::RenderObjects(const OpenGLScene& scene) const
    {
        EnableFaceCulling(GL_BACK, GL_CCW);
        OpenGLShader* shader = m_pShaderManager->GetShader(ShaderOpenGLTypes::RenderableObjects);
        shader->Bind();
        shader->SetUniform("u_view", MathUtils::ToGLM(m_pCamera->GetViewMatrix()));
        shader->SetUniform("u_projection", m_projectionMatrix);

        for (auto& [id, obj] : scene.GetObjects())
        {
            if (id >= 0)
            {
                shader->SetUniform("u_model", MathUtils::ToGLM(obj->GetModelMatrix()));
                glBindVertexArray(obj->GetVAO());
                glDrawElements(GL_TRIANGLES, obj->GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
            }
        }
        shader->UnBind();
        DisableFaceCulling();
    }

    void OpenGLRenderer::OpenGLRendererImpl::RenderGrid(const IRenderableObjectOpenGL& object) const
    {
        if (m_width == 0 || m_height == 0)
        {
            spdlog::error("Framebuffer dimensions are zero. Cannot render object.");
            return;
        }

        OpenGLShader* shader = m_pShaderManager->GetShader(ShaderOpenGLTypes::Grid);
        shader->Bind();

        glm::mat4 viewMatrix = MathUtils::ToGLM(m_pCamera->GetViewMatrix());

        shader->SetUniform("u_view", viewMatrix);
        shader->SetUniform("u_projection", m_projectionMatrix);

        glBindVertexArray(object.GetVAO());
        glBindBuffer(GL_ARRAY_BUFFER, object.GetVBO());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object.GetEBO());
        glDrawElements(GL_LINES, object.GetIndicesCount(), GL_UNSIGNED_INT, 0);

        shader->UnBind();
    }

    void OpenGLRenderer::OpenGLRendererImpl::UpdatePerspectiveMatrix(int width, int height)
    {
        float aspect = static_cast<float>(m_width) / static_cast<float>(m_height);
        m_projectionMatrix = glm::infinitePerspective(glm::radians(45.0f), aspect, 0.1f);
    }

    void OpenGLRenderer::OpenGLRendererImpl::BeginFrame() const
    {
        m_mainFBO.Bind();
        glViewport(0, 0, m_width, m_height);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRenderer::OpenGLRendererImpl::EndFrame() const
    {
        FrameBufferOpenGL::Unbind();
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
        glFrontFace(GL_CCW);
    }

    void OpenGLRenderer::OpenGLRendererImpl::PrepareFramebufferForNonLuminousPass() const
    {
        m_mainFBO.Bind();
        glViewport(0, 0, m_width, m_height);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRenderer::OpenGLRendererImpl::BindShadowMap(int textureUnit) const
    {
        glActiveTexture(GL_TEXTURE0 + textureUnit);
        glBindTexture(GL_TEXTURE_2D, m_shadowFBO.GetDepthTexture());
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

            lightAmbientValues.push_back({ 0.9f, 0.9f, 0.9f });
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
        std::unordered_map<int, Math::Vec3> lightCoords;
        const std::unordered_map<int, IRenderableObjectOpenGL*>& luminousObjsMap = scene.GetLuminousObjects();
        lightCoords.reserve(luminousObjsMap.size());

        for (const auto& [id, lightCaster] : luminousObjsMap)
        {
            lightCoords[id] = lightCaster->GetCenterPosition();
        }

        if (lightCoords.empty())
            return glm::mat4(1.0f);

        glm::vec3 lightPos = MathUtils::ToGLM(lightCoords.begin()->second);

        glm::vec3 sceneCenter(0.0f);
        glm::vec3 up(0.0f, 1.0f, 0.0f);

        glm::mat4 lightView = glm::lookAt(lightPos, sceneCenter, up);

        float orthoHalfSize = 10.0f;
        float nearPlane = 1.0f;
        float farPlane = 30.0f;
        glm::mat4 lightProj = glm::ortho(
            -orthoHalfSize, orthoHalfSize,
            -orthoHalfSize, orthoHalfSize,
            nearPlane, farPlane
        );

        return lightProj * lightView;
    }
}
