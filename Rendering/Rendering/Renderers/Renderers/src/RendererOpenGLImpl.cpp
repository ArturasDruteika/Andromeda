// RendererOpenGLImpl.cpp
#include "../include/RendererOpenGLImpl.hpp"

// If you use grid ID via SpecialIndices, include it here
//#include "../../../Scene/Support/include/SpecialIndices.hpp"

#include "../../../Utils/include/MathUtils.hpp"
#include "../../../Shaders/Shaders/include/ShaderOpenGL.hpp"
#include "../../../Shaders/Support/include/ShaderOpenGLTypes.hpp"
#include "Andromeda/Space/Objects/ILightObject.hpp"
#include "Andromeda/Space/Objects/ISurfaceObject.hpp"
#include "Andromeda/Space/Light/ILight.hpp"
#include "Andromeda/Space/Materials/IMaterial.hpp"

#include "glad/gl.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include "spdlog/spdlog.h"

#include <unordered_set>
#include <vector>

namespace Andromeda::Rendering
{
    RendererOpenGL::RendererOpenGLImpl::RendererOpenGLImpl()
        : m_isInitialized{ false }
        , m_directionalShadowResolution{ 2048 }
        , m_shadowCubeResolution{ 1024 }
        , m_shadowMapLightSpace{ glm::mat4{ 1.0f } }
        , m_mainFBO{}
        , m_directionalShadowFBO{}
        , m_pointShadowFBO{}
        , m_pShaderManager{ nullptr }
        , m_defaultVertexLayout{}
        , m_gpuMeshes{}
    {
        m_pShaderManager = new ShaderManager(true);
        SetCameraAspect(m_width, m_height);

        m_defaultVertexLayout = VertexLayout(
            {
                { VertexSemantic::Position, ComponentType::Float32, 3, false, 0 },
                { VertexSemantic::Normal,   ComponentType::Float32, 3, false, 0 },
                { VertexSemantic::Color0,   ComponentType::Float32, 2, false, 0 }
            }
        );
    }

    RendererOpenGL::RendererOpenGLImpl::~RendererOpenGLImpl()
    {
        DeInit();
    }

    bool RendererOpenGL::RendererOpenGLImpl::IsInitialized() const
    {
        return m_isInitialized;
    }

    bool RendererOpenGL::RendererOpenGLImpl::IsGridVisible() const
    {
        return m_isGridVisible;
    }

    unsigned int RendererOpenGL::RendererOpenGLImpl::GetFrameBufferObject() const
    {
        return m_mainFBO.GetId();
    }

    unsigned int RendererOpenGL::RendererOpenGLImpl::GetFrameBufferTexture() const
    {
        return m_mainFBO.GetColorTexture();
    }

    unsigned int RendererOpenGL::RendererOpenGLImpl::GetDepthRenderBuffer() const
    {
        return m_mainFBO.GetDepthRenderbuffer();
    }

    unsigned int RendererOpenGL::RendererOpenGLImpl::GetShadowMap() const
    {
        return m_directionalShadowFBO.GetDepthTexture();
    }

    unsigned int RendererOpenGL::RendererOpenGLImpl::GetPointShadowCube() const
    {
        return m_pointShadowFBO.GetDepthCubeTexture();
    }

    void RendererOpenGL::RendererOpenGLImpl::Init(int width, int height, bool illuminationMode)
    {
        if (width <= 0 || height <= 0)
        {
            spdlog::error("Invalid dimensions for initialization: {}x{}", width, height);
            return;
        }

        m_width = width;
        m_height = height;
        m_isIlluminationMode = illuminationMode;

        if (!m_mainFBO.Init(width, height, FrameBufferType::ColorDepth))
        {
            spdlog::error("Failed to create main framebuffer");
            return;
        }

        if (m_isIlluminationMode)
        {
            if (!m_directionalShadowFBO.Init(m_directionalShadowResolution, m_directionalShadowResolution, FrameBufferType::Depth))
            {
                spdlog::error("Failed to create shadow framebuffer");
                return;
            }
        }

        if (!m_pointShadowFBO.Init(m_shadowCubeResolution, m_shadowCubeResolution, FrameBufferType::DepthCube))
        {
            spdlog::error("Failed to create point-light cubemap shadow framebuffer");
            return;
        }

        ConfigurePointShadowDepthTexture();
        SetCameraAspect(width, height);
        m_isInitialized = true;
    }

    void RendererOpenGL::RendererOpenGLImpl::DeInit()
    {
        m_gpuMeshes.clear();

        delete m_pShaderManager;
        m_pShaderManager = nullptr;
        m_isInitialized = false;
    }

    void RendererOpenGL::RendererOpenGLImpl::Resize(int width, int height)
    {
        SizeControl::Resize(width, height);
        SetCameraAspect(width, height);
        m_mainFBO.Resize(width, height);
    }

    void RendererOpenGL::RendererOpenGLImpl::RenderFrame(IScene& scene)
    {
        if (!m_isInitialized)
        {
            return;
        }

        SyncGpuMeshes(scene);

        SetBackgroundColor(MathUtils::ToGLM(scene.GetBackgroundColor()));

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

    void RendererOpenGL::RendererOpenGLImpl::SyncGpuMeshes(const IScene& scene)
    {
        std::unordered_set<int> sceneIds;
        sceneIds.reserve(scene.GetObjects().size());

        for (const auto& [id, obj] : scene.GetObjects())
        {
            if (!obj)
            {
                continue;
            }

            sceneIds.insert(id);

            auto it = m_gpuMeshes.find(id);
            if (it == m_gpuMeshes.end())
            {
                GpuMeshOpenGL gpuMesh;
                gpuMesh.Create(obj->GetMesh(), m_defaultVertexLayout);
                m_gpuMeshes.emplace(id, std::move(gpuMesh));
            }
        }

        for (auto it = m_gpuMeshes.begin(); it != m_gpuMeshes.end();)
        {
            if (sceneIds.find(it->first) == sceneIds.end())
            {
                it = m_gpuMeshes.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }

    const GpuMeshOpenGL* RendererOpenGL::RendererOpenGLImpl::TryGetGpuMesh(int objectId) const
    {
        auto it = m_gpuMeshes.find(objectId);
        if (it == m_gpuMeshes.end())
        {
            return nullptr;
        }
        return &it->second;
    }

    void RendererOpenGL::RendererOpenGLImpl::ShadowMapDepthPass(const IScene& scene) const
    {
        EnableFaceCulling(GL_FRONT, GL_CCW);

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

        for (const auto& [id, obj] : scene.GetObjects())
        {
            if (!obj)
            {
                continue;
            }

            const int objId = obj->GetID();
            const GpuMeshOpenGL* mesh = TryGetGpuMesh(objId);
            if (!mesh)
            {
                continue;
            }

            depthShader->SetUniform("u_model", MathUtils::ToGLM(obj->GetModelMatrix()));
            glBindVertexArray(mesh->GetVAO());
            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh->GetIndexCount()), GL_UNSIGNED_INT, nullptr);
        }

        depthShader->UnBind();

        glBindFramebuffer(GL_FRAMEBUFFER, prevFBO);
        glDisable(GL_POLYGON_OFFSET_FILL);
        DisableFaceCulling();
    }

    void RendererOpenGL::RendererOpenGLImpl::ShadowCubeDepthPass(
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

        for (const auto& [id, obj] : scene.GetObjects())
        {
            if (!obj)
            {
                continue;
            }

            if (dynamic_cast<ILightObject*>(obj))
            {
                continue;
            }

            const int objId = obj->GetID();
            const GpuMeshOpenGL* mesh = TryGetGpuMesh(objId);
            if (!mesh)
            {
                continue;
            }

            depthCubeShader->SetUniform("u_model", MathUtils::ToGLM(obj->GetModelMatrix()));
            glBindVertexArray(mesh->GetVAO());
            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh->GetIndexCount()), GL_UNSIGNED_INT, nullptr);
        }

        depthCubeShader->UnBind();
        glBindFramebuffer(GL_FRAMEBUFFER, prevFBO);
        DisableFaceCulling();
    }

    void RendererOpenGL::RendererOpenGLImpl::RenderNonLuminousObjectsCombined(const IScene& scene, bool hasDir, bool hasPoint) const
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
        shader->SetUniform("u_projection", MathUtils::ToGLM(m_pCamera->GetProjection()));
        shader->SetUniform("u_cameraPosWS", MathUtils::ToGLM(m_pCamera->GetPosition()));

        if (hasDir)
        {
            shader->SetUniform("u_dirShadowMap", DIR_UNIT);
            shader->SetUniform("u_lightSpaceMatrix", m_shadowMapLightSpace);
            PopulateLightUniforms(*shader, scene);
        }

        if (hasPoint)
        {
            shader->SetUniform("u_pointShadowCube", POINT_UNIT);
            PopulatePointLightUniforms(*shader, scene);
        }

        RenderEachNonLuminousObject(*shader, scene);
        shader->UnBind();
        DisableFaceCulling();
    }

    void RendererOpenGL::RendererOpenGLImpl::RenderLuminousObjects(const IScene& scene) const
    {
        ShaderOpenGL* lumShader = m_pShaderManager->GetShader(ShaderOpenGLTypes::RenderableObjectsLuminous);
        lumShader->Bind();
        lumShader->SetUniform("u_view", MathUtils::ToGLM(m_pCamera->GetViewMatrix()));
        lumShader->SetUniform("u_projection", MathUtils::ToGLM(m_pCamera->GetProjection()));

        for (const auto& [id, obj] : scene.GetObjects())
        {
            if (!obj)
            {
                continue;
            }

            if (!dynamic_cast<ILightObject*>(obj))
            {
                continue;
            }

            const int objId = obj->GetID();
            const GpuMeshOpenGL* mesh = TryGetGpuMesh(objId);
            if (!mesh)
            {
                continue;
            }

            lumShader->SetUniform("u_model", MathUtils::ToGLM(obj->GetModelMatrix()));
            glBindVertexArray(mesh->GetVAO());
            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh->GetIndexCount()), GL_UNSIGNED_INT, nullptr);
        }

        lumShader->UnBind();
        DisableFaceCulling();
    }

    void RendererOpenGL::RendererOpenGLImpl::RenderObjects(const IScene& scene) const
    {
        EnableFaceCulling(GL_BACK, GL_CCW);

        ShaderOpenGL* shader = m_pShaderManager->GetShader(ShaderOpenGLTypes::RenderableObjects);
        shader->Bind();
        shader->SetUniform("u_view", MathUtils::ToGLM(m_pCamera->GetViewMatrix()));
        shader->SetUniform("u_projection", MathUtils::ToGLM(m_pCamera->GetProjection()));

        for (const auto& [id, obj] : scene.GetObjects())
        {
            if (!obj)
            {
                continue;
            }

            if (id < 0)
            {
                continue;
            }

            const int objId = obj->GetID();
            const GpuMeshOpenGL* mesh = TryGetGpuMesh(objId);
            if (!mesh)
            {
                continue;
            }

            shader->SetUniform("u_model", MathUtils::ToGLM(obj->GetModelMatrix()));
            glBindVertexArray(mesh->GetVAO());
            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh->GetIndexCount()), GL_UNSIGNED_INT, nullptr);
        }

        shader->UnBind();
        DisableFaceCulling();
    }

    void RendererOpenGL::RendererOpenGLImpl::RenderGrid(const GpuMeshOpenGL& mesh) const
    {
        if (m_width == 0 || m_height == 0)
        {
            spdlog::error("Framebuffer dimensions are zero. Cannot render grid.");
            return;
        }

        ShaderOpenGL* shader = m_pShaderManager->GetShader(ShaderOpenGLTypes::Grid);
        shader->Bind();

        shader->SetUniform("u_view", MathUtils::ToGLM(m_pCamera->GetViewMatrix()));
        shader->SetUniform("u_projection", MathUtils::ToGLM(m_pCamera->GetProjection()));

        glBindVertexArray(mesh.GetVAO());
        glDrawElements(GL_LINES, static_cast<GLsizei>(mesh.GetIndexCount()), GL_UNSIGNED_INT, nullptr);

        shader->UnBind();
    }

    void RendererOpenGL::RendererOpenGLImpl::PopulatePointLightUniforms(ShaderOpenGL& shader, const IScene& scene) const
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
            positions.push_back(MathUtils::ToGLM(pl->GetPosition()));
            intensities.push_back(pl->GetIntensity());
            ambient.push_back(MathUtils::ToGLM(pl->GeAmbient()));
            diffuse.push_back(MathUtils::ToGLM(pl->GetDiffuse()));
            specular.push_back(MathUtils::ToGLM(pl->GetSpecular()));

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

    void RendererOpenGL::RendererOpenGLImpl::RenderEachObjectDepthOnly(ShaderOpenGL& shader, const IScene& scene) const
    {
        for (const auto& [id, obj] : scene.GetObjects())
        {
            if (!obj)
            {
                continue;
            }

            if (id < 0)
            {
                continue;
            }

            const int objId = obj->GetID();
            const GpuMeshOpenGL* mesh = TryGetGpuMesh(objId);
            if (!mesh)
            {
                continue;
            }

            shader.SetUniform("u_model", MathUtils::ToGLM(obj->GetModelMatrix()));
            glBindVertexArray(mesh->GetVAO());
            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh->GetIndexCount()), GL_UNSIGNED_INT, nullptr);
        }
    }

    void RendererOpenGL::RendererOpenGLImpl::BeginFrame() const
    {
        m_mainFBO.Bind();
        glViewport(0, 0, m_width, m_height);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void RendererOpenGL::RendererOpenGLImpl::EndFrame() const
    {
        FrameBufferOpenGL::Unbind();
        glViewport(0, 0, m_width, m_height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void RendererOpenGL::RendererOpenGLImpl::LogFPS() const
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

    void RendererOpenGL::RendererOpenGLImpl::PrepareFramebufferForNonLuminousPass() const
    {
        m_mainFBO.Bind();
        glViewport(0, 0, m_width, m_height);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void RendererOpenGL::RendererOpenGLImpl::BindShadowMap(int textureUnit) const
    {
        glActiveTexture(GL_TEXTURE0 + textureUnit);
        glBindTexture(GL_TEXTURE_2D, m_directionalShadowFBO.GetDepthTexture());
    }

    void RendererOpenGL::RendererOpenGLImpl::RenderGridIfVisible(const IScene& scene) const
    {
        if (!m_isGridVisible)
        {
            return;
        }

        // If you use a special ID for grid, fetch it from scene and then draw its cached GPU mesh.
        // Example assumes the grid object exists in scene objects and its ID is returned by obj->GetID().
        //
        // If your grid is keyed by SpecialIndices::Grid in the map key, uncomment SpecialIndices include
        // and use that to find the object, then use its GetID() to lookup m_gpuMeshes.

        //auto itObj = scene.GetObjects().find(static_cast<int>(SpecialIndices::Grid));
        //if (itObj == scene.GetObjects().end() || !itObj->second)
        //{
        //    return;
        //}
        //const int gridId = itObj->second->GetID();
        //const GpuMeshOpenGL* mesh = TryGetGpuMesh(gridId);

        // Minimal generic approach: first object with negative key is treated as grid
        const auto& objects = scene.GetObjects();
        for (const auto& [id, obj] : objects)
        {
            if (id >= 0)
            {
                continue;
            }

            if (!obj)
            {
                continue;
            }

            const int gridId = obj->GetID();
            const GpuMeshOpenGL* mesh = TryGetGpuMesh(gridId);
            if (!mesh)
            {
                return;
            }

            RenderGrid(*mesh);
            return;
        }
    }

    void RendererOpenGL::RendererOpenGLImpl::PopulateLightUniforms(ShaderOpenGL& shader, const IScene& scene) const
    {
        const auto& directionalLightMap = scene.GetDirectionalLights();

        std::vector<glm::vec3> lightDirections;
        std::vector<glm::vec3> lightAmbientValues;
        std::vector<glm::vec3> lightDiffuseValues;
        std::vector<glm::vec3> lightSpecularValues;

        for (const auto& [id, directionalLight] : directionalLightMap)
        {
            lightDirections.push_back(MathUtils::ToGLM(directionalLight->GetDirection()));
            lightAmbientValues.push_back(glm::vec3(0.9f));
            lightDiffuseValues.push_back(MathUtils::ToGLM(directionalLight->GetDiffuse()));
            lightSpecularValues.push_back(MathUtils::ToGLM(directionalLight->GetSpecular()));
        }

        shader.SetUniform("u_numDirLights", static_cast<int>(lightDirections.size()));
        shader.SetUniform("u_dirLightDirections", lightDirections);
        shader.SetUniform("u_dirLightAmbient", lightAmbientValues);
        shader.SetUniform("u_dirLightDiffuse", lightDiffuseValues);
        shader.SetUniform("u_dirLightSpecular", lightSpecularValues);
    }

    void RendererOpenGL::RendererOpenGLImpl::RenderEachNonLuminousObject(ShaderOpenGL& shader, const IScene& scene) const
    {
        for (const auto& [id, obj] : scene.GetObjects())
        {
            if (!obj)
            {
                continue;
            }

            if (id < 0 || dynamic_cast<ILightObject*>(obj))
            {
                continue;
            }

			ISurfaceObject* surfaceObj = dynamic_cast<ISurfaceObject*>(obj);

            if (surfaceObj != nullptr)
            {
                const IMaterial* material = surfaceObj->GetMaterial();
                glm::mat3 normalMatrix = glm::inverseTranspose(MathUtils::ToGLM(obj->GetModelMatrix()));

                shader.SetUniform("u_materialAmbient", MathUtils::ToGLM(material->GetAmbient()));
                shader.SetUniform("u_materialDiffuse", MathUtils::ToGLM(material->GetDiffuse()));
                shader.SetUniform("u_materialSpecular", MathUtils::ToGLM(material->GetSpecular()));
                shader.SetUniform("u_materialShininess", material->GetShininess());

                shader.SetUniform("u_model", MathUtils::ToGLM(obj->GetModelMatrix()));
                shader.SetUniform("u_normalMatrix", normalMatrix);

                const int objId = obj->GetID();
                const GpuMeshOpenGL* mesh = TryGetGpuMesh(objId);
                if (!mesh)
                {
                    continue;
                }

                glBindVertexArray(mesh->GetVAO());
                glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh->GetIndexCount()), GL_UNSIGNED_INT, nullptr);
            }
        }
    }

    void RendererOpenGL::RendererOpenGLImpl::ConfigurePointShadowDepthTexture()
    {
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_pointShadowFBO.GetDepthCubeTexture());

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_COMPARE_MODE, GL_NONE);

        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }

    void RendererOpenGL::RendererOpenGLImpl::RenderLuminousMode(const IScene& scene)
    {
        const auto dirLights = scene.GetDirectionalLights();
        const bool hasDir = !dirLights.empty();

        const auto pointLights = scene.GetPointLights();
        const bool hasPoint = !pointLights.empty();

        if (hasDir)
        {
            m_shadowMapLightSpace = ComputeLightSpaceMatrix(scene);
            ShadowMapDepthPass(scene);
        }

        if (hasPoint)
        {
            const IPointLight* pl = pointLights.begin()->second;
            const glm::vec3 lightPos = MathUtils::ToGLM(pl->GetPosition());
            const float nearPlane = pl->GetShadowNearPlane();
            const float farPlane = pl->GetShadowFarPlane();
            ShadowCubeDepthPass(scene, lightPos, nearPlane, farPlane);
        }

        RenderNonLuminousObjectsCombined(scene, hasDir, hasPoint);
        RenderLuminousObjects(scene);

        RenderGridIfVisible(scene);
    }

    void RendererOpenGL::RendererOpenGLImpl::SetBackgroundColor(const glm::vec4& backgroundColor)
    {
        glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    }

    glm::mat4 RendererOpenGL::RendererOpenGLImpl::ComputeLightSpaceMatrix(const IScene& scene) const
    {
        const auto directionalLightMap = scene.GetDirectionalLights();
        const IDirectionalLight* light = directionalLightMap.begin()->second;

        glm::vec3 lightDirection = MathUtils::ToGLM(light->GetDirection());

        glm::vec3 up(0.0f, 1.0f, 0.0f);
        glm::vec3 lightPos = MathUtils::ToGLM(scene.GetSceneCenter()) - lightDirection * 20.0f;

        glm::mat4 lightView = glm::lookAt(lightPos, MathUtils::ToGLM(scene.GetSceneCenter()), up);
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
