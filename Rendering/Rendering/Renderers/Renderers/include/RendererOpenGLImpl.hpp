// RendererOpenGLImpl.hpp
#ifndef RENDERER__OPENGL_RENDERER_IMPL__HPP
#define RENDERER__OPENGL_RENDERER_IMPL__HPP

#include "../include/RendererOpenGL.hpp"
#include "../../Abstracts/include/Renderer.hpp"
#include "../../Abstracts/include/FaceCullingControlOpenGL.hpp"
#include "../../../OpenGL/Support/include/FrameBufferOpenGL.hpp"
#include "../../../Shaders/Shaders/include/ShaderManager.hpp"

#include "../../../Vertices/include/VertexLayouts.hpp"
#include "../../../OpenGL/Geometry/include/GpuMeshOpenGL.hpp"

#include "glm/glm.hpp"

#include <chrono>
#include <unordered_map>

namespace Andromeda::Rendering
{
    class RendererOpenGL::RendererOpenGLImpl
        : public Renderer
        , public FaceCullingControlOpenGL
    {
    public:
        RendererOpenGLImpl();
        ~RendererOpenGLImpl();

        RendererOpenGLImpl(const RendererOpenGLImpl& other) = delete;
        RendererOpenGLImpl& operator=(const RendererOpenGLImpl& other) = delete;
        RendererOpenGLImpl(RendererOpenGLImpl&& other) noexcept = delete;
        RendererOpenGLImpl& operator=(RendererOpenGLImpl&& other) noexcept = delete;

        bool IsInitialized() const;
        bool IsGridVisible() const;
        unsigned int GetFrameBufferObject() const;
        unsigned int GetFrameBufferTexture() const;
        unsigned int GetDepthRenderBuffer() const;
        unsigned int GetShadowMap() const;
        unsigned int GetPointShadowCube() const;

        void Init(int width, int height, bool illuminationMode = false);
        void DeInit();
        void RenderFrame(IScene& scene);
        void Resize(int width, int height);

    private:
        void SyncGpuMeshes(const IScene& scene);

        const GpuMeshOpenGL* TryGetGpuMesh(int objectId) const;

        void ShadowMapDepthPass(const IScene& scene) const;
        void ShadowCubeDepthPass(
            const IScene& scene,
            const glm::vec3& lightPos,
            float nearPlane,
            float farPlane
        ) const;

        void RenderNonLuminousObjectsCombined(const IScene& scene, const ICamera& rCamera, bool hasDir, bool hasPoint) const;
        void RenderLuminousObjects(const IScene& scene, const ICamera& rCamera) const;
        void RenderObjects(const IScene& scene, const ICamera& rCamera) const;

        void RenderGrid(const GpuMeshOpenGL& mesh) const;

        void PopulatePointLightUniforms(ShaderOpenGL& shader, const IScene& scene) const;
        void RenderEachObjectDepthOnly(ShaderOpenGL& shader, const IScene& scene) const;

        void BeginFrame() const;
        void EndFrame() const;
        void LogFPS() const;

        void PrepareFramebufferForNonLuminousPass() const;
        void BindShadowMap(int textureUnit) const;

        void RenderGridIfVisible(const IScene& scene) const;

        void PopulateLightUniforms(ShaderOpenGL& shader, const IScene& scene) const;
        void RenderEachNonLuminousObject(ShaderOpenGL& shader, const IScene& scene) const;

        void ConfigurePointShadowDepthTexture();
        void RenderLuminousMode(const IScene& scene, const ICamera& rCamera);

        void SetBackgroundColor(const glm::vec4& backgroundColor);
        glm::mat4 ComputeLightSpaceMatrix(const IScene& scene) const;

    private:
        bool m_isInitialized;
        int m_directionalShadowResolution;
        int m_shadowCubeResolution;

        glm::mat4 m_shadowMapLightSpace;

        FrameBufferOpenGL m_mainFBO;
        FrameBufferOpenGL m_directionalShadowFBO;
        FrameBufferOpenGL m_pointShadowFBO;

        ShaderManager* m_pShaderManager;

        VertexLayout m_defaultVertexLayout;
        std::unordered_map<int, GpuMeshOpenGL> m_gpuMeshes;

        mutable std::chrono::steady_clock::time_point m_lastFrameTime = std::chrono::steady_clock::now();
    };
}

#endif // RENDERER__OPENGL_RENDERER_IMPL__HPP
