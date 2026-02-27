#ifndef RENDERING__OPENGL__SUPPORT__SHADOW_RENDERER_OPENGL__HPP
#define RENDERING__OPENGL__SUPPORT__SHADOW_RENDERER_OPENGL__HPP


#include "FrameBufferOpenGL.hpp"
#include "FaceCullingControlOpenGL.hpp"
#include "../../../Shaders/Shaders/include/ShaderManager.hpp"
#include "../../Support/include/MeshCacheOpenGL.hpp"
#include "Andromeda/Space/Light/IDirectionalLight.hpp"
#include "Andromeda/Space/Light/IPointLight.hpp"
#include "Andromeda/Space/Objects/IGeometricObject.hpp"
#include "Andromeda/Space/Transformations/ITransformable.hpp"
#include "pch.hpp"


namespace Andromeda::Rendering
{
    class ShadowRendererOpenGL
    {
    public:
        static void RenderDirectionalShadowMap(
            const std::unordered_map<int, IGeometricObject*>& objects,
            const std::unordered_map<int, ITransformable*>& objectTransforms,
            FrameBufferOpenGL& shadowFbo,
            int resolution,
            const glm::mat4& lightSpaceMatrix,
            ShaderManager& shaderManager,
            MeshCacheOpenGL& meshCache,
            FaceCullingControlOpenGL& culling
        );

        static void RenderPointShadowCube(
            const std::unordered_map<int, IGeometricObject*>& objects,
            const std::unordered_map<int, ITransformable*>& objectTransforms,
            FrameBufferOpenGL& pointShadowFbo,
            int resolution,
            const glm::vec3& lightPos,
            float nearPlane,
            float farPlane,
            ShaderOpenGL& pointLightShader,
            MeshCacheOpenGL& meshCache,
            FaceCullingControlOpenGL& culling
        );

        // TODO: consider making it a void and calculating ONLY when the scene state has been changed
        static glm::mat4 ComputeLightSpaceMatrix(
            const std::unordered_map<int, const IDirectionalLight*>& directionalLights,
            const Math::Vec3& sceneCenter
        );

        static void PopulateDirectionalLightUniforms(
            ShaderOpenGL& shader,
            const std::unordered_map<int, const IDirectionalLight*>& dirLights
        );

        static void PopulatePointLightUniforms(
            ShaderOpenGL& shader,
            const std::unordered_map<int, const IPointLight*>& pointLights
        );

    private:
        static void ConfigurePointShadowPass(
            FrameBufferOpenGL& pointShadowFbo,
            int resolution,
            FaceCullingControlOpenGL& culling,
            int& prevFbo
        );

        static std::vector<glm::mat4> BuildPointShadowMatrices(
            const glm::vec3& lightPos,
            float nearPlane,
            float farPlane
        );

        static void RenderPointShadowObjects(
            const std::unordered_map<int, IGeometricObject*>& objects,
            const std::unordered_map<int, ITransformable*>& objectTransforms,
            ShaderOpenGL& shader,
            MeshCacheOpenGL& meshCache
        );

        static void FinishPointShadowPass(
            int prevFbo,
            FaceCullingControlOpenGL& culling
        );
    };
}


#endif // RENDERING__OPENGL__SUPPORT__SHADOW_RENDERER_OPENGL__HPP
