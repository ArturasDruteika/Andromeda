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
#include "FileOperations.hpp"
#include "Colors.hpp"
#include "glad/gl.h"
#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include "spdlog/spdlog.h"


namespace Andromeda::Rendering
{
    constexpr Space::Color BACKGROUND_COLOR_DEFAULT{ 0.0f, 0.0f, 0.0f, 1.0f };

    OpenGLRenderer::OpenGLRendererImpl::OpenGLRendererImpl()
        : m_isInitialized{ false }
        , m_lightSpace{ glm::mat4(1.0f) }
        , m_pShaderManager{ nullptr }
		, m_shadowCubeSize{ 1024 }
    {
        glClearColor(
            BACKGROUND_COLOR_DEFAULT.r,
            BACKGROUND_COLOR_DEFAULT.g,
            BACKGROUND_COLOR_DEFAULT.b,
            BACKGROUND_COLOR_DEFAULT.a
        );
        m_pShaderManager = new ShaderManager(true);
        SetCameraAspect(m_width, m_height);
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

        // Point-light shadow map: cubemap depth (new)
        if (!m_pointShadowFBO.Init(width, height, FrameBufferType::DepthCube))
        {
            spdlog::error("Failed to create point-light cubemap shadow framebuffer");
            return;
        }

        // Optional: hardware depth comparison for samplerCubeShadow
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_pointShadowFBO.GetDepthCubeTexture());
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

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
        if (m_isIlluminationMode)
        {
            m_shadowFBO.Resize(width, height);
            // If you want it to scale with window, clamp to a square:
            int cube = std::max(128, std::min(width, height)); // or keep a fixed 1024
            m_pointShadowFBO.Resize(cube, cube);
            // Optional: hardware depth comparison for samplerCubeShadow
            glBindTexture(GL_TEXTURE_CUBE_MAP, m_pointShadowFBO.GetDepthCubeTexture());
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
            glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
        }
    }

    void OpenGLRenderer::OpenGLRendererImpl::RenderFrame(IScene& scene)
    {
        if (!m_isInitialized)
            return;

        BeginFrame();

        if (m_isIlluminationMode)
        {
            // Directional light(s)
            const std::unordered_map<int, const DirectionalLight*> dirLights = scene.GetDirectionalLights();
            const bool hasDir = !dirLights.empty();

            // Point light(s)
            const std::unordered_map<int, const PointLight*> pointLights = scene.GetPointLights(); // assumes API exists
            const bool hasPoint = !pointLights.empty();

            if (hasDir)
            {
                m_lightSpace = ComputeLightSpaceMatrix(scene);
                ShadowMapDepthPass(scene, m_lightSpace);
            }

            if (hasPoint)
            {
                const PointLight* pl = pointLights.begin()->second; // pick first (extend as needed)
                const glm::vec3 lightPos = pl->GetPosition();
                const float nearPlane = pl->GetShadowNearPlane();   // or 0.1f
                const float farPlane = pl->GetShadowFarPlane();    // or light radius
                ShadowMapDepthPassPoint(scene, lightPos, nearPlane, farPlane);
            }

            // Lighting pass that can read both shadow maps
            RenderNonLuminousObjectsCombined(scene, hasDir, hasPoint);
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
        return m_shadowFBO.GetDepthTexture();
    }

    unsigned int OpenGLRenderer::OpenGLRendererImpl::GetPointShadowCube() const
    {
        return m_pointShadowFBO.GetDepthCubeTexture();
    }

    void OpenGLRenderer::OpenGLRendererImpl::ShadowMapDepthPass(const IScene& scene, const glm::mat4& lightSpace) const
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

        ShaderOpenGL* depthShader = m_pShaderManager->GetShader(ShaderOpenGLTypes::ShadowMap);
        depthShader->Bind();
        depthShader->SetUniform("u_lightSpaceMatrix", lightSpace);

        for (auto& [id, obj] : scene.GetObjects())
        {
            depthShader->SetUniform("u_model", MathUtils::ToGLM(obj->GetModelMatrix()));
			IRenderableObjectOpenGL* renderableObj = dynamic_cast<IRenderableObjectOpenGL*>(obj);
            glBindVertexArray(renderableObj->GetVAO());
            glDrawElements(GL_TRIANGLES, obj->GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
        }

        depthShader->UnBind();

        glBindFramebuffer(GL_FRAMEBUFFER, prevFBO);
        DisableFaceCulling();
    }

    void OpenGLRenderer::OpenGLRendererImpl::ShadowMapDepthPassPoint(const IScene& scene, const glm::vec3& lightPos, float nearPlane, float farPlane) const
    {
        EnableFaceCulling(GL_FRONT, GL_CCW);

        int prevFBO;
        glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &prevFBO);

        m_pointShadowFBO.Bind();
        glViewport(0, 0, m_pointShadowFBO.GetWidth(), m_pointShadowFBO.GetHeight());
        glEnable(GL_DEPTH_TEST);
        glClear(GL_DEPTH_BUFFER_BIT);

        ShaderOpenGL* depthCubeShader = m_pShaderManager->GetShader(ShaderOpenGLTypes::PointShadowCubeMap);
        depthCubeShader->Bind();

        const glm::mat4 proj = glm::perspective(glm::radians(90.0f), 1.0f, nearPlane, farPlane);

        // build 6 face matrices using vectors
        std::vector<glm::vec3> ups{
            { 0, -1,  0}, { 0, -1,  0},
            { 0,  0,  1}, { 0,  0, -1},
            { 0, -1,  0}, { 0, -1,  0}
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

        // assuming your ShaderOpenGL supports vector uploads
        depthCubeShader->SetUniform("u_shadowMatrices[0]", shadowMatrices);

        depthCubeShader->SetUniform("u_lightPos", lightPos);
        depthCubeShader->SetUniform("u_farPlane", farPlane);

        for (auto& [id, obj] : scene.GetObjects())
        {
            IRenderableObjectOpenGL* r = dynamic_cast<IRenderableObjectOpenGL*>(obj);
            depthCubeShader->SetUniform("u_model", MathUtils::ToGLM(obj->GetModelMatrix()));
            glBindVertexArray(r->GetVAO());
            glDrawElements(GL_TRIANGLES, obj->GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
        }

        depthCubeShader->UnBind();
        glBindFramebuffer(GL_FRAMEBUFFER, prevFBO);
        DisableFaceCulling();
    }

    void OpenGLRenderer::OpenGLRendererImpl::RenderNonLuminousObjects(const IScene& scene, const glm::mat4& lightSpace) const
    {
        EnableFaceCulling(GL_BACK, GL_CCW);
        const int SHADOW_UNIT = 5;
        glActiveTexture(GL_TEXTURE0 + SHADOW_UNIT);
        glBindTexture(GL_TEXTURE_2D, m_shadowFBO.GetDepthTexture());

        ShaderOpenGL* nlShader = m_pShaderManager->GetShader(ShaderOpenGLTypes::RenderableObjectsNonLuminous);
        nlShader->Bind();

        nlShader->SetUniform("u_view", MathUtils::ToGLM(m_pCamera->GetViewMatrix()));
        nlShader->SetUniform("u_projection", m_pCamera->GetProjection());
        nlShader->SetUniform("u_viewPos", MathUtils::ToGLM(m_pCamera->GetPosition()));
        nlShader->SetUniform("u_lightSpaceMatrix", lightSpace);
        nlShader->SetUniform("u_shadowMap", SHADOW_UNIT);

        PopulateLightUniforms(*nlShader, scene);
        RenderEachNonLuminousObject(*nlShader, scene);

        nlShader->UnBind();
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
            glBindTexture(GL_TEXTURE_2D, m_shadowFBO.GetDepthTexture());
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
        shader->SetUniform("u_viewPos", MathUtils::ToGLM(m_pCamera->GetPosition()));
        shader->SetUniform("u_hasDirShadow", hasDir ? 1 : 0);
        shader->SetUniform("u_hasPointShadow", hasPoint ? 1 : 0);
        if (hasDir) 
            shader->SetUniform("u_shadowMap2D", DIR_UNIT);
        if (hasPoint) 
            shader->SetUniform("u_shadowCube", POINT_UNIT);

        // *** MISSING BEFORE: pass light-space for dir shadows ***
        if (hasDir)
        {
            shader->SetUniform("u_lightSpaceMatrix", m_lightSpace);
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

    void OpenGLRenderer::OpenGLRendererImpl::RenderPointShadowMap(
        const IScene& scene, 
        const glm::vec3& lightPos, 
        float nearZ,
        float farZ
    )
    {
        // 1) Build the 6 face matrices
        glm::mat4 proj = glm::perspective(glm::radians(90.0f), 1.0f, nearZ, farZ);
        std::vector<glm::mat4> mats;
        mats.reserve(6);

        mats.push_back(proj * glm::lookAt(lightPos, lightPos + glm::vec3(1, 0, 0), glm::vec3(0, -1, 0)));
        mats.push_back(proj * glm::lookAt(lightPos, lightPos + glm::vec3(-1, 0, 0), glm::vec3(0, -1, 0)));
        mats.push_back(proj * glm::lookAt(lightPos, lightPos + glm::vec3(0, 1, 0), glm::vec3(0, 0, 1)));
        mats.push_back(proj * glm::lookAt(lightPos, lightPos + glm::vec3(0, -1, 0), glm::vec3(0, 0, -1)));
        mats.push_back(proj * glm::lookAt(lightPos, lightPos + glm::vec3(0, 0, 1), glm::vec3(0, -1, 0)));
        mats.push_back(proj * glm::lookAt(lightPos, lightPos + glm::vec3(0, 0, -1), glm::vec3(0, -1, 0)));

        // 2) Bind layered depth-cubemap FBO
        glViewport(0, 0, m_shadowFBO.GetWidth(), m_shadowFBO.GetHeight());
        glBindFramebuffer(GL_FRAMEBUFFER, m_shadowFBO.GetId());
        glClear(GL_DEPTH_BUFFER_BIT);
        glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE); // depth-only

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT); // helps acne; try FRONT for shadow pass

        // 3) Use point-shadow shader
        ShaderOpenGL* sh = m_pShaderManager->GetShader(ShaderOpenGLTypes::PointShadowCubeMap);
        sh->Bind();
        sh->SetUniform("u_lightPos", lightPos);
        sh->SetUniform("u_farPlane", farZ);
        sh->SetUniform("u_shadowMatrices[0]", mats); // implement helper that uploads 6 mat4s

        // 4) Draw scene (per-object u_model)
        RenderEachObjectDepthOnly(*sh, scene); // draw all occluders; sets u_model for each mesh

        sh->UnBind();

        // 5) Restore state
        glCullFace(GL_BACK);
        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void OpenGLRenderer::OpenGLRendererImpl::PopulatePointLightUniforms(ShaderOpenGL& shader, const IScene& scene) const
    {
        const auto& pointLightMap = scene.GetPointLights();

        std::vector<glm::vec3> positions;
        std::vector<glm::vec3> ambient;
        std::vector<glm::vec3> diffuse;
        std::vector<glm::vec3> specular;

        std::vector<float> constant;
        std::vector<float> linear;
        std::vector<float> quadratic;

        std::vector<float> farPlanes;

        positions.reserve(pointLightMap.size());
        ambient.reserve(pointLightMap.size());
        diffuse.reserve(pointLightMap.size());
        specular.reserve(pointLightMap.size());
        constant.reserve(pointLightMap.size());
        linear.reserve(pointLightMap.size());
        quadratic.reserve(pointLightMap.size());
        farPlanes.reserve(pointLightMap.size());

        for (const auto& [id, pl] : pointLightMap)
        {
            positions.push_back(pl->GetPosition());

            // If your PointLight exposes GetAmbient(), use that.
            // Otherwise keep a subtle base ambient to avoid pitch-black areas.
            ambient.push_back(glm::vec3(0.05f));
            diffuse.push_back(pl->GetDiffuse());
            specular.push_back(pl->GetSpecular());

            // If your PointLight exposes attenuation getters, use them;
            // otherwise fall back to sensible defaults.
            float c = 1.0f;
            float l = 0.09f;
            float q = 0.032f;

            if constexpr (true) // replace with feature-detection if needed
            {
                // Wrap in try/catch or `if constexpr` with traits if your API differs.
                // Assuming these exist:
                c = pl->GetAttenuationConstant();
                l = pl->GetAttenuationLinear();
                q = pl->GetAttenuationQuadratic();
            }

            constant.push_back(c);
            linear.push_back(l);
            quadratic.push_back(q);

            farPlanes.push_back(pl->GetShadowFarPlane());
        }

        shader.SetUniform("u_numPointLights", static_cast<int>(positions.size()));
        shader.SetUniform("u_pointLightPositions", positions);
        shader.SetUniform("u_pointLightAmbient", ambient);
        shader.SetUniform("u_pointLightDiffuse", diffuse);
        shader.SetUniform("u_pointLightSpecular", specular);

        // Attenuation & far-planes (used for cubemap shadow distance normalization in the fragment shader)
        shader.SetUniform("u_pointLightConstant", constant);
        shader.SetUniform("u_pointLightLinear", linear);
        shader.SetUniform("u_pointLightQuadratic", quadratic);
        shader.SetUniform("u_pointLightFarPlane", farPlanes);
    }

    void OpenGLRenderer::OpenGLRendererImpl::RenderEachObjectDepthOnly(ShaderOpenGL& shader, const IScene& scene) const
    {
        // Draw *all* occluders (generally all visible geometry with a VAO).
        // If you want to exclude helpers (like the grid), keep the id < 0 check.
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
            //spdlog::info("FPS: {:.2f}", fps);
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
        glBindTexture(GL_TEXTURE_2D, m_shadowFBO.GetDepthTexture());
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

        for (const auto& [id, light] : directionalLightMap)
        {
            glm::vec3 lightDirGLM = light->GetDirection();
            lightDirections.push_back(lightDirGLM);

            lightAmbientValues.push_back(glm::vec3(0.9f));  // optional: could be fetched from light
            lightDiffuseValues.push_back(light->GetDiffuse());
            lightSpecularValues.push_back(light->GetSpecular());
        }

        shader.SetUniform("u_numLights", static_cast<int>(lightDirections.size()));
        shader.SetUniform("u_directionLight", lightDirections);
        shader.SetUniform("u_ambientLight", lightAmbientValues);
        shader.SetUniform("u_diffuseLight", lightDiffuseValues);
        shader.SetUniform("u_specularLight", lightSpecularValues);
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
            glm::mat3 normalMatrix = glm::inverseTranspose(glm::mat3(MathUtils::ToGLM(obj->GetModelMatrix())));

            shader.SetUniform("u_ambientMaterial", MathUtils::ToGLM(material.GetAmbient()));
            shader.SetUniform("u_diffuseMaterial", MathUtils::ToGLM(material.GetDiffuse()));
            shader.SetUniform("u_specularMaterial", MathUtils::ToGLM(material.GetSpecular()));
            shader.SetUniform("u_shininessMaterial", material.GetShininess());
            shader.SetUniform("u_model", MathUtils::ToGLM(obj->GetModelMatrix()));
            shader.SetUniform("u_normalMatrix", normalMatrix);

            IRenderableObjectOpenGL* renderableObj = dynamic_cast<IRenderableObjectOpenGL*>(obj);
            glBindVertexArray(renderableObj->GetVAO());
            glDrawElements(GL_TRIANGLES, obj->GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
        }
    }

    glm::mat4 OpenGLRenderer::OpenGLRendererImpl::ComputeLightSpaceMatrix(const IScene& scene) const
    {
        std::unordered_map<int, Math::Vec3> lightCoords;
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
