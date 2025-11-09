#include "glad/gl.h"
#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include "spdlog/spdlog.h"
#include "FileOperations.hpp"
#include "Colors.hpp"
#include "../include/OpenGLRendererImpl.hpp"
#include "../../../Scene/Support/include/SpecialIndices.hpp"
#include "../../../Utils/include/MathUtils.hpp"
#include "../../../Light/Abstracts/include/LuminousBehavior.hpp"
#include "../../../Light/Abstracts/include/NonLuminousBehavior.hpp"
#include "../../../Light/Support/include/LightData.hpp"
#include "../../../RenderableObjects/Objects/include/GridOpenGL.hpp"
#include "../../../Light/LightTypes/include/PointLight.hpp"
#include "../../../Shaders/Shaders/include/ShaderOpenGL.hpp"
#include "../../../Shaders/Support/include/ShaderOpenGLTypes.hpp"
#include "../../../RenderableObjects/Interfaces/include/IRenderableObjectOpenGL.hpp"
#include "../../../RenderableObjects/Objects/include/SkyroomOpenGL.hpp"


namespace Andromeda::Rendering
{
    OpenGLRenderer::OpenGLRendererImpl::OpenGLRendererImpl()
        : m_isInitialized{ false }
        , m_shadowMapLightSpace{ glm::mat4(1.0f) }
        , m_pShaderManager{ nullptr }
        , m_directionalShadowResolution{ 2048 }
        , m_shadowCubeResolution{ 1024 }
    {
        m_pShaderManager = new ShaderManager(true);
        SetCameraAspect(m_width, m_height);
    }

    OpenGLRenderer::OpenGLRendererImpl::~OpenGLRendererImpl()
    {
        DeInit();
    }

    bool OpenGLRenderer::OpenGLRendererImpl::IsInitialized() const
    {
        return m_isInitialized;
    }

    bool OpenGLRenderer::OpenGLRendererImpl::IsGridVisible() const
    {
        return m_isGridVisible;
    }

    unsigned int OpenGLRenderer::OpenGLRendererImpl::GetFrameBufferObject() const
    {
        return m_mainFBO.GetId();
    }

    unsigned int OpenGLRenderer::OpenGLRendererImpl::GetFrameBufferTexture() const
    {
        return m_mainFBO.GetColorTexture();
    }

    unsigned int OpenGLRenderer::OpenGLRendererImpl::GetDepthRenderBuffer() const
    {
        return m_mainFBO.GetDepthRenderbuffer();
    }

    unsigned int OpenGLRenderer::OpenGLRendererImpl::GetShadowMap() const
    {
        return m_directionalShadowFBO.GetDepthTexture();
    }

    unsigned int OpenGLRenderer::OpenGLRendererImpl::GetPointShadowCube() const
    {
        return m_pointShadowFBO.GetDepthCubeTexture();
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
            if (!m_directionalShadowFBO.Init(m_directionalShadowResolution, m_directionalShadowResolution, FrameBufferType::Depth))
            {
                spdlog::error("Failed to create shadow framebuffer");
                return;
            }
        }

        // Point-light shadow map: cubemap depth
        if (!m_pointShadowFBO.Init(m_shadowCubeResolution, m_shadowCubeResolution, FrameBufferType::DepthCube))
        {
            spdlog::error("Failed to create point-light cubemap shadow framebuffer");
            return;
        }

        ConfigurePointShadowDepthTexture();
        SetCameraAspect(width, height);
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
        SizeControl::Resize(width, height);
        SetCameraAspect(width, height);
        m_mainFBO.Resize(width, height);
    }

    void OpenGLRenderer::OpenGLRendererImpl::RenderFrame(IScene& scene)
    {
        if (!m_isInitialized)
            return;

        SetBackgroundColor(scene.GetBackgroundColor());

        BeginFrame();

        if (m_isIlluminationMode)
        {
            RenderLuminousMode(scene);
        }
        else
        {
            RenderObjects(scene);
        }

        EndFrame();
        LogFPS();
    }

    void OpenGLRenderer::OpenGLRendererImpl::ShadowMapDepthPass(const IScene& scene) const
    {
        EnableFaceCulling(GL_FRONT, GL_CCW);

        if (m_width <= 0 || m_height <= 0)
        {
            spdlog::error("Shadow map dimensions are zero. Cannot render shadow map.");
            return;
        }

        int prevFBO;
        glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &prevFBO);

        m_directionalShadowFBO.Bind();
        glViewport(0, 0, m_directionalShadowResolution, m_directionalShadowResolution);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_DEPTH_BUFFER_BIT);

        DisableFaceCulling();
        EnableFaceCulling(GL_FRONT, GL_CW);

        glEnable(GL_POLYGON_OFFSET_FILL);
        glPolygonOffset(2.0f, 4.0f);

        ShaderOpenGL* depthShader = m_pShaderManager->GetShader(ShaderOpenGLTypes::ShadowMap);
        depthShader->Bind();
        depthShader->SetUniform("u_lightSpaceMatrix", m_shadowMapLightSpace);

        for (auto& [id, obj] : scene.GetObjects())
        {
            depthShader->SetUniform("u_model", MathUtils::ToGLM(obj->GetModelMatrix()));
            IRenderableObjectOpenGL* renderableObj = dynamic_cast<IRenderableObjectOpenGL*>(obj);
            glBindVertexArray(renderableObj->GetVAO());
            glDrawElements(GL_TRIANGLES, obj->GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
        }

        depthShader->UnBind();

        glBindFramebuffer(GL_FRAMEBUFFER, prevFBO);
        glDisable(GL_POLYGON_OFFSET_FILL);
        DisableFaceCulling();
    }

    void OpenGLRenderer::OpenGLRendererImpl::ShadowCubeDepthPass(
        const IScene& scene, 
        const glm::vec3& lightPos, 
        float nearPlane, 
        float farPlane
    ) const
    {
        EnableFaceCulling(GL_FRONT, GL_CCW);

        int prevFBO;
        glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &prevFBO);

        m_pointShadowFBO.Bind();
        glViewport(0, 0, m_shadowCubeResolution, m_shadowCubeResolution);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_DEPTH_BUFFER_BIT);

        ShaderOpenGL* depthCubeShader = m_pShaderManager->GetShader(ShaderOpenGLTypes::PointShadowCubeMap);
        depthCubeShader->Bind();

        const glm::mat4 proj = glm::perspective(glm::radians(90.0f), 1.0f, nearPlane, farPlane);

        std::vector<glm::vec3> ups{
            { 0, -1,  0}, 
            { 0, -1,  0},
            { 0,  0,  1}, 
            { 0,  0, -1},
            { 0, -1,  0}, 
            { 0, -1,  0}
        };

        std::vector<glm::vec3> targets{
            lightPos + glm::vec3(1, 0, 0),
            lightPos + glm::vec3(-1, 0, 0),
            lightPos + glm::vec3(0, 1, 0),
            lightPos + glm::vec3(0,-1, 0),
            lightPos + glm::vec3(0, 0, 1),
            lightPos + glm::vec3(0, 0,-1)
        };

        std::vector<glm::mat4> shadowMatrices(6);
        for (std::size_t i = 0; i < shadowMatrices.size(); ++i)
        {
            shadowMatrices[i] = proj * glm::lookAt(lightPos, targets[i], ups[i]);
        }

        depthCubeShader->SetUniform("u_shadowMatrices[0]", shadowMatrices);
        depthCubeShader->SetUniform("u_lightPos", lightPos);
        depthCubeShader->SetUniform("u_farPlane", farPlane);

        for (auto& [id, obj] : scene.GetObjects())
        {
            if (obj->IsLuminous())
                continue;

            IRenderableObjectOpenGL* r = dynamic_cast<IRenderableObjectOpenGL*>(obj);
            depthCubeShader->SetUniform("u_model", MathUtils::ToGLM(obj->GetModelMatrix()));
            glBindVertexArray(r->GetVAO());
            glDrawElements(GL_TRIANGLES, obj->GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
        }

        depthCubeShader->UnBind();
        glBindFramebuffer(GL_FRAMEBUFFER, prevFBO);
        DisableFaceCulling();
    }

    void OpenGLRenderer::OpenGLRendererImpl::RenderNonLuminousObjectsCombined(const IScene& scene, bool hasDir, bool hasPoint) const
    {
        glViewport(0, 0, m_width, m_height);
        EnableFaceCulling(GL_BACK, GL_CCW);

        const int DIR_UNIT = 5;
        const int POINT_UNIT = 6;

        if (hasDir)
        {
            glActiveTexture(GL_TEXTURE0 + DIR_UNIT);
            glBindTexture(GL_TEXTURE_2D, m_directionalShadowFBO.GetDepthTexture());
        }
        if (hasPoint)
        {
            glActiveTexture(GL_TEXTURE0 + POINT_UNIT);
            glBindTexture(GL_TEXTURE_CUBE_MAP, m_pointShadowFBO.GetDepthCubeTexture());
        }
        
        ShaderOpenGL* shader = m_pShaderManager->GetShader(ShaderOpenGLTypes::RenderableObjectsNonLuminous);
        shader->Bind();

        shader->SetUniform("u_view", MathUtils::ToGLM(m_pCamera->GetViewMatrix()));
        shader->SetUniform("u_projection", m_pCamera->GetProjection());
        shader->SetUniform("u_cameraPosWS", MathUtils::ToGLM(m_pCamera->GetPosition()));
        
        if (hasDir)
        {
            shader->SetUniform("u_dirShadowMap", DIR_UNIT);
            shader->SetUniform("u_lightSpaceMatrix", m_shadowMapLightSpace);
        }

        if (hasPoint)
        {
            shader->SetUniform("u_pointShadowCube", POINT_UNIT);
        }

        PopulateLightUniforms(*shader, scene);
        PopulatePointLightUniforms(*shader, scene);
        RenderEachNonLuminousObject(*shader, scene);
        shader->UnBind();
        DisableFaceCulling();
    }

    void OpenGLRenderer::OpenGLRendererImpl::RenderLuminousObjects(const IScene& scene) const
    {
        ShaderOpenGL* lumShader = m_pShaderManager->GetShader(ShaderOpenGLTypes::RenderableObjectsLuminous);
        lumShader->Bind();
        lumShader->SetUniform("u_view", MathUtils::ToGLM(m_pCamera->GetViewMatrix()));
        lumShader->SetUniform("u_projection", m_pCamera->GetProjection());

        for (auto& [id, obj] : scene.GetObjects())
        {
            if (obj->IsLuminous())
            {
                lumShader->SetUniform("u_model", MathUtils::ToGLM(obj->GetModelMatrix()));
                IRenderableObjectOpenGL* renderableObj = dynamic_cast<IRenderableObjectOpenGL*>(obj);
                glBindVertexArray(renderableObj->GetVAO());
                glDrawElements(GL_TRIANGLES, obj->GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
            }
        }
        lumShader->UnBind();
        DisableFaceCulling();
    }

    void OpenGLRenderer::OpenGLRendererImpl::RenderObjects(const IScene& scene) const
    {
        EnableFaceCulling(GL_BACK, GL_CCW);
        ShaderOpenGL* shader = m_pShaderManager->GetShader(ShaderOpenGLTypes::RenderableObjects);
        shader->Bind();
        shader->SetUniform("u_view", MathUtils::ToGLM(m_pCamera->GetViewMatrix()));
        shader->SetUniform("u_projection", m_pCamera->GetProjection());

        for (auto& [id, obj] : scene.GetObjects())
        {
            if (id >= 0)
            {
                shader->SetUniform("u_model", MathUtils::ToGLM(obj->GetModelMatrix()));
                IRenderableObjectOpenGL* renderableObj = dynamic_cast<IRenderableObjectOpenGL*>(obj);
                glBindVertexArray(renderableObj->GetVAO());
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

        ShaderOpenGL* shader = m_pShaderManager->GetShader(ShaderOpenGLTypes::Grid);
        shader->Bind();

        glm::mat4 viewMatrix = MathUtils::ToGLM(m_pCamera->GetViewMatrix());

        shader->SetUniform("u_view", viewMatrix);
        shader->SetUniform("u_projection", m_pCamera->GetProjection());

        glBindVertexArray(object.GetVAO());
        glBindBuffer(GL_ARRAY_BUFFER, object.GetVBO());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object.GetEBO());
        glDrawElements(GL_LINES, object.GetIndicesCount(), GL_UNSIGNED_INT, 0);

        shader->UnBind();
    }

    void OpenGLRenderer::OpenGLRendererImpl::PopulatePointLightUniforms(ShaderOpenGL& shader, const IScene& scene) const
    {
        const auto& pointLightMap = scene.GetPointLights();

        std::vector<glm::vec3> positions, ambient, diffuse, specular;
        std::vector<float> intensities, constant, linear, quadratic, farPlanes;

        positions.reserve(pointLightMap.size());
        intensities.reserve(pointLightMap.size());
        ambient.reserve(pointLightMap.size());
        diffuse.reserve(pointLightMap.size());
        specular.reserve(pointLightMap.size());
        constant.reserve(pointLightMap.size());
        linear.reserve(pointLightMap.size());
        quadratic.reserve(pointLightMap.size());
        farPlanes.reserve(pointLightMap.size());

        for (const auto& [id, pl] : pointLightMap)
        {
            const Light& light = pl->GetLight();

            positions.push_back(pl->GetPosition());
            intensities.push_back(light.GetIntensity());
            ambient.push_back(light.GeAmbient());
            diffuse.push_back(light.GetDiffuse());
            specular.push_back(light.GetSpecular());
            
            constant.push_back(pl->GetAttenuationConstant());
            linear.push_back(pl->GetAttenuationLinear());
            quadratic.push_back(pl->GetAttenuationQuadratic());

            farPlanes.push_back(pl->GetShadowFarPlane());
        }

        shader.SetUniform("u_numPointLights", static_cast<int>(positions.size()));
        shader.SetUniform("u_pointLightPositions", positions);
        shader.SetUniform("u_pointLightIntensity", intensities);
        shader.SetUniform("u_pointLightAmbient", ambient);
        shader.SetUniform("u_pointLightDiffuse", diffuse);
        shader.SetUniform("u_pointLightSpecular", specular);

        shader.SetUniform("u_pointLightConstant", constant);
        shader.SetUniform("u_pointLightLinear", linear);
        shader.SetUniform("u_pointLightQuadratic", quadratic);
        shader.SetUniform("u_pointLightFarPlanes", farPlanes);
    }

    void OpenGLRenderer::OpenGLRendererImpl::RenderEachObjectDepthOnly(ShaderOpenGL& shader, const IScene& scene) const
    {
        for (const auto& [id, obj] : scene.GetObjects())
        {
            if (id < 0)
            {
                continue;
            }

            IRenderableObjectOpenGL* renderable = dynamic_cast<IRenderableObjectOpenGL*>(obj);
            if (!renderable)
            {
                continue;
            }

            shader.SetUniform("u_model", MathUtils::ToGLM(obj->GetModelMatrix()));
            glBindVertexArray(renderable->GetVAO());
            glDrawElements(GL_TRIANGLES, obj->GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
        }
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
        glBindTexture(GL_TEXTURE_2D, m_directionalShadowFBO.GetDepthTexture());
    }

    void OpenGLRenderer::OpenGLRendererImpl::RenderGridIfVisible(const IScene& scene) const
    {
        if (m_isGridVisible)
        {
            const auto& objects = scene.GetObjects();
            auto it = objects.find(static_cast<int>(SpecialIndices::Grid));
            if (it != objects.end())
            {
                IRenderableObjectOpenGL* renderableObj = dynamic_cast<IRenderableObjectOpenGL*>(it->second);
                RenderGrid(*renderableObj);
            }
        }
    }

    void OpenGLRenderer::OpenGLRendererImpl::PopulateLightUniforms(ShaderOpenGL& shader, const IScene& scene) const
    {
        const auto& directionalLightMap = scene.GetDirectionalLights();

        std::vector<glm::vec3> lightDirections;
        std::vector<glm::vec3> lightAmbientValues;
        std::vector<glm::vec3> lightDiffuseValues;
        std::vector<glm::vec3> lightSpecularValues;

        for (const auto& [id, directionalLight] : directionalLightMap)
        {
            const Light& light = directionalLight->GetLight();
            glm::vec3 lightDirGLM = directionalLight->GetDirection();
            lightDirections.push_back(lightDirGLM);

            lightAmbientValues.push_back(glm::vec3(0.9f)); // consider lowering for testing shadows
            lightDiffuseValues.push_back(light.GetDiffuse());
            lightSpecularValues.push_back(light.GetSpecular());
        }

        shader.SetUniform("u_numDirLights", static_cast<int>(lightDirections.size()));
        shader.SetUniform("u_dirLightDirections", lightDirections);
        shader.SetUniform("u_dirLightAmbient", lightAmbientValues);
        shader.SetUniform("u_dirLightDiffuse", lightDiffuseValues);
        shader.SetUniform("u_dirLightSpecular", lightSpecularValues);
    }

    void OpenGLRenderer::OpenGLRendererImpl::RenderEachNonLuminousObject(ShaderOpenGL& shader, const IScene& scene) const
    {
        for (const auto& [id, obj] : scene.GetObjects())
        {
            if (id < 0 || obj->IsLuminous())
                continue;

            NonLuminousBehavior* nonLum = dynamic_cast<NonLuminousBehavior*>(obj->GetLightBehavior());
            if (!nonLum)
                continue;

            Material material = nonLum->GetMaterial();
            // TODO: Recalculate normal matrix IF the state of the objet has changed.
            glm::mat3 normalMatrix = glm::inverseTranspose(MathUtils::ToGLM(obj->GetModelMatrix()));

            shader.SetUniform("u_materialAmbient", MathUtils::ToGLM(material.GetAmbient()));
            shader.SetUniform("u_materialDiffuse", MathUtils::ToGLM(material.GetDiffuse()));
            shader.SetUniform("u_materialSpecular", MathUtils::ToGLM(material.GetSpecular()));
            shader.SetUniform("u_materialShininess", material.GetShininess());

            shader.SetUniform("u_model", MathUtils::ToGLM(obj->GetModelMatrix()));
            shader.SetUniform("u_normalMatrix", normalMatrix); // required by vertex shader

            IRenderableObjectOpenGL* renderableObj = dynamic_cast<IRenderableObjectOpenGL*>(obj);
            glBindVertexArray(renderableObj->GetVAO());
            glDrawElements(GL_TRIANGLES, obj->GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
        }
    }

    void OpenGLRenderer::OpenGLRendererImpl::ConfigurePointShadowDepthTexture()
    {
        // Manual compare setup for depth cubemap
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_pointShadowFBO.GetDepthCubeTexture());

        // Filters (NEAREST easiest for debugging)
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        // Wrapping
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        // Disable hardware depth comparison - we'll do it manually in the shader
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_COMPARE_MODE, GL_NONE);

        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }

    void OpenGLRenderer::OpenGLRendererImpl::RenderLuminousMode(const IScene& scene)
    {
        const std::unordered_map<int, const DirectionalLight*> dirLights = scene.GetDirectionalLights();
        const bool hasDir = !dirLights.empty();

        const std::unordered_map<int, const PointLight*> pointLights = scene.GetPointLights();
        const bool hasPoint = !pointLights.empty();

        if (hasDir)
        {
            m_shadowMapLightSpace = ComputeLightSpaceMatrix(scene);
            ShadowMapDepthPass(scene);
        }

        if (hasPoint)
        {
            // TODO: later implement point shadows for ALL point lights casters
            const PointLight* pl = pointLights.begin()->second;
            const glm::vec3 lightPos = pl->GetPosition();
            const float nearPlane = pl->GetShadowNearPlane();
            const float farPlane = pl->GetShadowFarPlane();
            ShadowCubeDepthPass(scene, lightPos, nearPlane, farPlane);
        }

        RenderNonLuminousObjectsCombined(scene, hasDir, hasPoint);
        RenderLuminousObjects(scene);
    }

    void OpenGLRenderer::OpenGLRendererImpl::SetBackgroundColor(const glm::vec4& backgroundColor)
    {
        glClearColor(
            backgroundColor.r,
            backgroundColor.g,
            backgroundColor.b,
            backgroundColor.a
        );
    }

    glm::mat4 OpenGLRenderer::OpenGLRendererImpl::ComputeLightSpaceMatrix(const IScene& scene) const
    {
        const std::unordered_map<int, const DirectionalLight*> directionalLightMap = scene.GetDirectionalLights();
        const DirectionalLight* light = directionalLightMap.begin()->second;
        glm::vec3 lightDirection = light->GetDirection();

        glm::vec3 up(0.0f, 1.0f, 0.0f);
        glm::vec3 lightPos = scene.GetSceneCenter() - lightDirection * 20.0f;

        glm::mat4 lightView = glm::lookAt(lightPos, scene.GetSceneCenter(), up);

        glm::mat4 lightProj = glm::ortho(
            -light->GetLightOrthographicHalfSize(),
            light->GetLightOrthographicHalfSize(),
            -light->GetLightOrthographicHalfSize(),
            light->GetLightOrthographicHalfSize(),
            light->GetLightNearPlane(),
            light->GetLightFarPlane()
        );

        return lightProj * lightView;
    }
}
