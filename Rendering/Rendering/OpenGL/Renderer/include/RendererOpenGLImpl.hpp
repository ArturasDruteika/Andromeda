#ifndef RENDERER__OPENGL_RENDERER_IMPL__HPP
#define RENDERER__OPENGL_RENDERER_IMPL__HPP


#include "../../Geometry/include/GpuMeshOpenGL.hpp"
#include "../../Support/include/FaceCullingControlOpenGL.hpp"
#include "../../Support/include/FrameBufferOpenGL.hpp"
#include "../../Support/include/FPSCounter.hpp"
#include "../../Support/include/MeshCacheOpenGL.hpp"
#include "../../Support/include/TextRendererOpenGL.hpp"
#include "../../../Renderers/Renderers/include/RendererOpenGL.hpp"
#include "../../../Renderers/Abstracts/include/GridControl.hpp"
#include "../../../Renderers/Abstracts/include/IlluminationControl.hpp"
#include "../../../Renderers/Abstracts/include/SizeControl.hpp"
#include "../../../Shaders/Shaders/include/ShaderManager.hpp"
#include "../../../Vertices/include/VertexLayouts.hpp"
#include "pch.hpp"


namespace Andromeda::Rendering
{
    class RendererOpenGL::RendererOpenGLImpl
        : public GridControl
        , public IlluminationControl
        , public SizeControl
    {
    public:
        RendererOpenGLImpl();
        ~RendererOpenGLImpl();

        RendererOpenGLImpl(const RendererOpenGLImpl& other) = delete;
        RendererOpenGLImpl& operator=(const RendererOpenGLImpl& other) = delete;
        RendererOpenGLImpl(RendererOpenGLImpl&& other) noexcept = delete;
        RendererOpenGLImpl& operator=(RendererOpenGLImpl&& other) noexcept = delete;

        // Getters
        bool IsInitialized() const;
        void* GetFrameTextureHandle() const;

        void Init(int width, int height, bool illuminationMode = false);
        void DeInit();
        void RenderFrame(IScene& scene);
        void Resize(int width, int height);

    private:
        void RenderNonLuminousObjectsCombined(const IScene& scene, const ICamera& rCamera, bool hasDir, bool hasPoint) const;
        void RenderLuminousObjects(
            const std::unordered_map<int, IGeometricObject*>& objects,
            const ICamera& rCamera
        ) const;
        void RenderObjects(
            const std::unordered_map<int, IGeometricObject*>& objects,
            const ICamera& rCamera
        ) const;
        void RenderGrid(const GpuMeshOpenGL& mesh) const;
        void BeginFrame() const;
        void EndFrame() const;
        void LogFPS();
        void PrepareFramebufferForNonLuminousPass() const;
        void BindShadowMap(int textureUnit) const;
        void RenderGridIfVisible(const IScene& scene) const;
        void RenderEachNonLuminousObject(
            ShaderOpenGL& shader, 
            const std::unordered_map<int, IGeometricObject*>& objects
        ) const;
        void ConfigurePointShadowDepthTexture();
        void RenderLuminousMode(const IScene& scene, const ICamera& rCamera);
        void SetBackgroundColor(const glm::vec4& backgroundColor);
        

    private:
        bool m_isInitialized;
        int m_directionalShadowResolution;
        int m_shadowCubeResolution;
        glm::mat4 m_shadowMapLightSpace;
        FrameBufferOpenGL m_mainFBO;
        FrameBufferOpenGL m_directionalShadowFBO;
        FrameBufferOpenGL m_pointShadowFBO;
        FaceCullingControlOpenGL m_faceCullingControlOpenGL;
        MeshCacheOpenGL m_meshCache;
        ShaderManager* m_pShaderManager;
        VertexLayout m_defaultVertexLayout;
        TextRendererOpenGL m_textRenderer;
        FpsCounter m_fpsCounter;
        mutable std::chrono::steady_clock::time_point m_lastFrameTime = std::chrono::steady_clock::now();
    };
}

#endif // RENDERER__OPENGL_RENDERER_IMPL__HPP
