#include "../include/RendererOpenGLImpl.hpp"
#include "../../Support/include/ShadowRendererOpenGL.hpp"
#include "../../../Utils/include/MathUtils.hpp"
#include "../../../Shaders/Shaders/include/ShaderOpenGL.hpp"
#include "../../../Shaders/Support/include/ShaderOpenGLTypes.hpp"
#include "Andromeda/Space/Objects/ILightObject.hpp"
#include "Andromeda/Space/Objects/ISurfaceObject.hpp"
#include "Andromeda/Space/Materials/IMaterial.hpp"
#include "pch.hpp"

#include "glad/gl.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/matrix_inverse.hpp"
#include "spdlog/spdlog.h"


namespace Andromeda::Rendering
{
    constexpr int DEFAULT_DIRECTIONAL_SHADOW_RESOLUTION = 2048;
    constexpr int DEFAULT_POINT_SHADOW_RESOLUTION = 1024;

    RendererOpenGL::RendererOpenGLImpl::RendererOpenGLImpl()
        : m_isInitialized{ false }
        , m_directionalShadowResolution{ DEFAULT_DIRECTIONAL_SHADOW_RESOLUTION }
        , m_shadowCubeResolution{ DEFAULT_POINT_SHADOW_RESOLUTION }
        , m_shadowMapLightSpace{ glm::mat4{ 1.0f } }
        , m_pShaderManager{ nullptr }
    {
        m_pShaderManager = new ShaderManager(true);
        m_defaultVertexLayout = VertexLayout(
            {
                { VertexSemantic::Position, ComponentType::Float32, 3, false, 0 },
                { VertexSemantic::Color0,   ComponentType::Float32, 4, true, sizeof(Math::Vec3) },
                { VertexSemantic::Normal,   ComponentType::Float32, 3, true, sizeof(Math::Vec3) + sizeof(Math::Vec4) }
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

    void* RendererOpenGL::RendererOpenGLImpl::GetFrameTextureHandle() const
    {
        return reinterpret_cast<void*>(static_cast<uintptr_t>(m_mainFBO.GetColorTexture()));
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
        m_textRenderer.Init();

        m_isInitialized = true;
    }

    void RendererOpenGL::RendererOpenGLImpl::DeInit()
    {
        m_meshCache.Clear();

        delete m_pShaderManager;
        m_pShaderManager = nullptr;
        m_isInitialized = false;
    }

    void RendererOpenGL::RendererOpenGLImpl::Resize(int width, int height)
    {
        SizeControl::Resize(width, height);
        m_mainFBO.Resize(width, height);
    }

    void RendererOpenGL::RendererOpenGLImpl::RenderFrame(IScene& scene)
    {
        if (!m_isInitialized)
            return;

        const ICamera* pCamera = scene.GetActiveCamera();
        if (!pCamera)
            return;

        m_meshCache.Sync(scene.GetObjects(), m_defaultVertexLayout);

        SetBackgroundColor(MathUtils::ToGLM(scene.GetBackgroundColor()));
        BeginFrame();

        if (m_isIlluminationMode)
        {
            RenderLuminousMode(scene, *pCamera);
        }
        else
        {
            RenderObjects(scene.GetObjects(), scene.GetObjectTransforms(), *pCamera);
        }

        EndFrame();
		LogFPS();
    }

    void RendererOpenGL::RendererOpenGLImpl::RenderNonLuminousObjectsCombined(const IScene& scene, const ICamera& rCamera, bool hasDir, bool hasPoint) const
    {
        glViewport(0, 0, m_width, m_height);
        m_faceCullingControlOpenGL.EnableFaceCulling(GL_BACK, GL_CCW);

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

        shader->SetUniform("u_view", MathUtils::ToGLM(rCamera.GetViewMatrix()));
        shader->SetUniform("u_projection", glm::transpose(MathUtils::ToGLM(rCamera.GetProjection())));
        shader->SetUniform("u_cameraPosWS", MathUtils::ToGLM(rCamera.GetPosition()));

        if (hasDir)
        {
            shader->SetUniform("u_dirShadowMap", DIR_UNIT);
            shader->SetUniform("u_lightSpaceMatrix", m_shadowMapLightSpace);
            ShadowRendererOpenGL::PopulateDirectionalLightUniforms(*shader, scene.GetDirectionalLights());
        }

        if (hasPoint)
        {
            shader->SetUniform("u_pointShadowCube", POINT_UNIT);
            ShadowRendererOpenGL::PopulatePointLightUniforms(*shader, scene.GetPointLights());
        }

        RenderEachNonLuminousObject(*shader, scene.GetObjects(), scene.GetObjectTransforms());
        shader->UnBind();
        m_faceCullingControlOpenGL.DisableFaceCulling();
    }

    void RendererOpenGL::RendererOpenGLImpl::RenderLuminousObjects(
        const std::unordered_map<int, IGeometricObject*>& objects,
        const std::unordered_map<int, ITransformable*>& objectTransforms,
        const ICamera& rCamera
    ) const
    {
        ShaderOpenGL* lumShader = m_pShaderManager->GetShader(ShaderOpenGLTypes::RenderableObjectsLuminous);
        lumShader->Bind();
        lumShader->SetUniform("u_view", MathUtils::ToGLM(rCamera.GetViewMatrix()));
        lumShader->SetUniform("u_projection", MathUtils::ToGLM(rCamera.GetProjection()));

        for (const auto& [id, obj] : objects)
        {
            if (!obj)
            {
                continue;
            }

            if (!dynamic_cast<ILightObject*>(obj))
            {
                continue;
            }

            std::unordered_map<int, ITransformable*>::const_iterator transformIt =
                objectTransforms.find(id);
            if (transformIt == objectTransforms.end() || !transformIt->second)
            {
                continue;
            }

            const int objId = obj->GetID();
            const GpuMeshOpenGL* mesh = m_meshCache.TryGet(objId);
            if (!mesh)
            {
                continue;
            }

            lumShader->SetUniform("u_model", MathUtils::ToGLM(transformIt->second->GetModelMatrix()));
            glBindVertexArray(mesh->GetVAO());
            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh->GetIndexCount()), GL_UNSIGNED_INT, nullptr);
        }

        lumShader->UnBind();
        m_faceCullingControlOpenGL.DisableFaceCulling();
    }

    void RendererOpenGL::RendererOpenGLImpl::RenderObjects(
        const std::unordered_map<int, IGeometricObject*>& objects,
        const std::unordered_map<int, ITransformable*>& objectTransforms,
        const ICamera& rCamera) const 
    { 
        m_faceCullingControlOpenGL.EnableFaceCulling(GL_BACK, GL_CCW);
        ShaderOpenGL* shader = m_pShaderManager->GetShader(ShaderOpenGLTypes::RenderableObjects); 
        shader->Bind(); 

        shader->SetUniform("u_view", MathUtils::ToGLM(rCamera.GetViewMatrix()));
        shader->SetUniform("u_projection", glm::transpose(MathUtils::ToGLM(rCamera.GetProjection())));

        for (const auto& [id, obj] : objects) 
        { 
            if (!obj || id < 0) 
                continue;

            std::unordered_map<int, ITransformable*>::const_iterator transformIt = objectTransforms.find(id);
            if (transformIt == objectTransforms.end() || !transformIt->second)
                continue;

            int objID = obj->GetID(); 
            const GpuMeshOpenGL* mesh = m_meshCache.TryGet(objID);

            if (!mesh) 
                continue;

            const Math::Mat4& modelMatrix = transformIt->second->GetModelMatrix(); 
            shader->SetUniform("u_model", MathUtils::ToGLM(modelMatrix)); 
            glBindVertexArray(mesh->GetVAO()); 
            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh->GetIndexCount()), GL_UNSIGNED_INT, nullptr); 
        } 

        shader->UnBind(); 
        m_faceCullingControlOpenGL.DisableFaceCulling();
    }

    void RendererOpenGL::RendererOpenGLImpl::RenderGrid(const GpuMeshOpenGL& mesh) const
    {
        //if (m_width == 0 || m_height == 0)
        //{
        //    spdlog::error("Framebuffer dimensions are zero. Cannot render grid.");
        //    return;
        //}

        //ShaderOpenGL* shader = m_pShaderManager->GetShader(ShaderOpenGLTypes::Grid);
        //shader->Bind();

        //shader->SetUniform("u_view", MathUtils::ToGLM(m_pCamera->GetViewMatrix()));
        //shader->SetUniform("u_projection", MathUtils::ToGLM(m_pCamera->GetProjection()));

        //glBindVertexArray(mesh.GetVAO());
        //glDrawElements(GL_LINES, static_cast<GLsizei>(mesh.GetIndexCount()), GL_UNSIGNED_INT, nullptr);

        //shader->UnBind();
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
        // Blit FBO color to default framebuffer
        glBindFramebuffer(GL_READ_FRAMEBUFFER, m_mainFBO.GetId());
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

        glBlitFramebuffer(
            0, 0, m_width, m_height,          // src rect
            0, 0, m_width, m_height,          // dst rect
            GL_COLOR_BUFFER_BIT,
            GL_NEAREST
        );

        // If you also want to blit depth (for further drawing on default):
        // glBlitFramebuffer(0, 0, m_width, m_height,
        //                   0, 0, m_width, m_height,
        //                   GL_DEPTH_BUFFER_BIT, GL_NEAREST);

        // Return to default framebuffer bound
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void RendererOpenGL::RendererOpenGLImpl::LogFPS()
    {
        // Update FPS counter
        m_fpsCounter.FrameTick();
        float fps = m_fpsCounter.GetSmoothedFps();

        ShaderOpenGL* textShader = m_pShaderManager->GetShader(ShaderOpenGLTypes::Text);
        if (!textShader)
        {
            spdlog::error("Text shader is null (ShaderOpenGLTypes::Text).");
            return;
        }

        if (!m_textRenderer.IsValid())
        {
            spdlog::error("TextRendererOpenGL is not valid (VAO/VBO not created).");
            return;
        }

        // Draw directly to default framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, m_width, m_height);

        textShader->Bind();

        // Y-down orthographic projection to match stb_easy_font coordinates
        glm::mat4 proj = glm::ortho(
            0.0f,
            static_cast<float>(m_width),
            static_cast<float>(m_height),
            0.0f
        );

        textShader->SetUniform("u_projection", proj);
        textShader->SetUniform("u_color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)); // white

        GLboolean depthWasEnabled = glIsEnabled(GL_DEPTH_TEST);
        GLboolean cullWasEnabled = glIsEnabled(GL_CULL_FACE);

        glDisable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE);

        // Compose FPS text
        const std::string fpsText = "FPS: " + std::to_string(static_cast<int>(fps));

        // Top-left-ish corner, in pixels
        m_textRenderer.RenderText(fpsText, 10.0f, 20.0f, 2.0f);

        if (depthWasEnabled)
        {
            glEnable(GL_DEPTH_TEST);
        }
        if (cullWasEnabled)
        {
            glEnable(GL_CULL_FACE);
        }

        textShader->UnBind();

        GLenum err = glGetError();
        if (err != GL_NO_ERROR)
        {
            spdlog::error("OpenGL error after RenderText: {}", err);
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

        //std::unordered_map<int, IGeometricObject*>::const_iterator itObj =
        //    scene.GetObjects().find(static_cast<int>(SpecialIndices::Grid));
        //if (itObj == scene.GetObjects().end() || !itObj->second)
        //{
        //    return;
        //}
        //const int gridId = itObj->second->GetID();
        //const GpuMeshOpenGL* mesh = TryGetGpuMesh(gridId);

        // Minimal generic approach: first object with negative key is treated as grid
        const std::unordered_map<int, IGeometricObject*>& objects = scene.GetObjects();
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
            const GpuMeshOpenGL* mesh = m_meshCache.TryGet(gridId);
            if (!mesh)
            {
                return;
            }

            RenderGrid(*mesh);
            return;
        }
    }

    void RendererOpenGL::RendererOpenGLImpl::RenderEachNonLuminousObject(
        ShaderOpenGL& shader,
        const std::unordered_map<int, IGeometricObject*>& objects,
        const std::unordered_map<int, ITransformable*>& objectTransforms
    ) const
    {
        for (const auto& [id, obj] : objects)
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
                std::unordered_map<int, ITransformable*>::const_iterator transformIt =
                    objectTransforms.find(id);
                if (transformIt == objectTransforms.end() || !transformIt->second)
                {
                    continue;
                }

                const IMaterial* material = surfaceObj->GetMaterial();
                glm::mat3 normalMatrix = glm::inverseTranspose(
                    MathUtils::ToGLM(transformIt->second->GetModelMatrix())
                );

                shader.SetUniform("u_materialAmbient", MathUtils::ToGLM(material->GetAmbient()));
                shader.SetUniform("u_materialDiffuse", MathUtils::ToGLM(material->GetDiffuse()));
                shader.SetUniform("u_materialSpecular", MathUtils::ToGLM(material->GetSpecular()));
                shader.SetUniform("u_materialShininess", material->GetShininess());

                shader.SetUniform("u_model", MathUtils::ToGLM(transformIt->second->GetModelMatrix()));
                shader.SetUniform("u_normalMatrix", normalMatrix);

                const int objId = obj->GetID();
                const GpuMeshOpenGL* mesh = m_meshCache.TryGet(objId);
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

    void RendererOpenGL::RendererOpenGLImpl::RenderLuminousMode(const IScene& scene, const ICamera& rCamera)
    {
        const std::unordered_map<int, const IDirectionalLight*>& dirLights = scene.GetDirectionalLights();
        const bool hasDir = !dirLights.empty();

        const std::unordered_map<int, const IPointLight*>& pointLights = scene.GetPointLights();
        const bool hasPoint = !pointLights.empty();


        if (hasDir)
        {
            m_shadowMapLightSpace = ShadowRendererOpenGL::ComputeLightSpaceMatrix(
                scene.GetDirectionalLights(),
                scene.GetSceneCenter()
            );

            ShadowRendererOpenGL::RenderDirectionalShadowMap(
                scene.GetObjects(),
                scene.GetObjectTransforms(),
                m_directionalShadowFBO,
                m_directionalShadowResolution,
                m_shadowMapLightSpace,
                *m_pShaderManager,
                m_meshCache,
                m_faceCullingControlOpenGL
            );
        }

        if (hasPoint)
        {
            const IPointLight* pl = pointLights.begin()->second;
            const glm::vec3 lightPos = MathUtils::ToGLM(pl->GetPosition());
            const float nearPlane = pl->GetShadowNearPlane();
            const float farPlane = pl->GetShadowFarPlane();

            ShadowRendererOpenGL::RenderPointShadowCube(
                scene.GetObjects(),
                scene.GetObjectTransforms(),
                m_pointShadowFBO,
                m_shadowCubeResolution,
                lightPos,
                nearPlane,
                farPlane,
                *(m_pShaderManager->GetShader(ShaderOpenGLTypes::PointShadowCubeMap)),
                m_meshCache,
                m_faceCullingControlOpenGL
            );
        }

        RenderNonLuminousObjectsCombined(scene, rCamera, hasDir, hasPoint);
        RenderLuminousObjects(scene.GetObjects(), scene.GetObjectTransforms(), rCamera);

        RenderGridIfVisible(scene);
    }

    void RendererOpenGL::RendererOpenGLImpl::SetBackgroundColor(const glm::vec4& backgroundColor)
    {
        glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    }
}
