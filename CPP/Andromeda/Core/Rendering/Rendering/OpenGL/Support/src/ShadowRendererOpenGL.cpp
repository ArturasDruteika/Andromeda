#include "../include/ShadowRendererOpenGL.hpp"
#include "../../../Shaders/Shaders/include/ShaderOpenGL.hpp"
#include "../../../Shaders/Support/include/ShaderOpenGLTypes.hpp"
#include "../../../Utils/include/MathUtils.hpp"
#include "Andromeda/Space/Objects/ILightObject.hpp"

#include "glad/gl.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/matrix_inverse.hpp"


namespace Andromeda::Rendering
{
    constexpr int CUBEMAP_FACES = 6;
    constexpr float CUBEMAP_FOV = 90.0f;
    constexpr float CUBEMAP_ASPECT = 1.0f;
    constexpr float LIGHT_OFFSET = 20.0f;
    constexpr glm::vec3 UP = glm::vec3(0.0f, 1.0f, 0.0f);
    constexpr glm::vec3 CUBEMAP_UPS[CUBEMAP_FACES] = {
        glm::vec3(0.0f, -1.0f, 0.0f), // POSITIVE_X
        glm::vec3(0.0f, -1.0f, 0.0f), // NEGATIVE_X
        glm::vec3(0.0f, 0.0f, 1.0f),  // POSITIVE_Y
        glm::vec3(0.0f, 0.0f, -1.0f), // NEGATIVE_Y
        glm::vec3(0.0f, -1.0f, 0.0f), // POSITIVE_Z
        glm::vec3(0.0f, -1.0f, 0.0f)  // NEGATIVE_Z
    };
    constexpr glm::vec3 CUBEMAP_TARGETS[CUBEMAP_FACES] = {
        glm::vec3(1.0f, 0.0f, 0.0f),   // POSITIVE_X
        glm::vec3(-1.0f, 0.0f, 0.0f),  // NEGATIVE_X
        glm::vec3(0.0f, 1.0f, 0.0f),   // POSITIVE_Y
        glm::vec3(0.0f, -1.0f, 0.0f),  // NEGATIVE_Y
        glm::vec3(0.0f, 0.0f, 1.0f),   // POSITIVE_Z
        glm::vec3(0.0f, 0.0f, -1.0f)   // NEGATIVE_Z
    };

    void ShadowRendererOpenGL::RenderDirectionalShadowMap(
        const std::unordered_map<int, IGeometricObject*>& objects,
        const std::unordered_map<int, ITransformable*>& objectTransforms,
        FrameBufferOpenGL& shadowFbo,
        int resolution,
        const glm::mat4& lightSpaceMatrix,
        ShaderManager& shaderManager,
        MeshCacheOpenGL& meshCache,
        FaceCullingControlOpenGL& culling
    )
    {
        culling.EnableFaceCulling(GL_FRONT, GL_CCW);

        int prevFBO;
        glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &prevFBO);

        shadowFbo.Bind();
        glViewport(0, 0, resolution, resolution);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_DEPTH_BUFFER_BIT);

        glEnable(GL_POLYGON_OFFSET_FILL);
        glPolygonOffset(2.0f, 4.0f);

        ShaderOpenGL* depthShader = shaderManager.GetShader(ShaderOpenGLTypes::ShadowMap);
        depthShader->Bind();
        depthShader->SetUniform("u_lightSpaceMatrix", lightSpaceMatrix);

        for (const auto& [id, obj] : objects)
        {
            if (!obj)
            {
                continue;
            }

            std::unordered_map<int, ITransformable*>::const_iterator transformIt =
                objectTransforms.find(id);
            if (transformIt == objectTransforms.end() || !transformIt->second)
            {
                continue;
            }

            const GpuMeshOpenGL* mesh = meshCache.TryGet(obj->GetID());
            if (!mesh)
            {
                continue;
            }

            depthShader->SetUniform("u_model", MathUtils::ToGLM(transformIt->second->GetModelMatrix()));
            glBindVertexArray(mesh->GetVAO());
            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh->GetIndexCount()), GL_UNSIGNED_INT, nullptr);
        }

        depthShader->UnBind();

        glBindFramebuffer(GL_FRAMEBUFFER, prevFBO);
        glDisable(GL_POLYGON_OFFSET_FILL);
        culling.DisableFaceCulling();
    }

    void ShadowRendererOpenGL::RenderPointShadowCube(
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
    )
    {
        int prevFBO;
        ConfigurePointShadowPass(pointShadowFbo, resolution, culling, prevFBO);

        pointLightShader.Bind();

        const std::vector<glm::mat4> matrices = BuildPointShadowMatrices(lightPos, nearPlane, farPlane);

        pointLightShader.SetUniform("u_shadowMatrices[0]", matrices);
        pointLightShader.SetUniform("u_lightPos", lightPos);
        pointLightShader.SetUniform("u_farPlane", farPlane);

        RenderPointShadowObjects(objects, objectTransforms, pointLightShader, meshCache);

        pointLightShader.UnBind();
        FinishPointShadowPass(prevFBO, culling);
    }

    glm::mat4 ShadowRendererOpenGL::ComputeLightSpaceMatrix(
        const std::unordered_map<int, const IDirectionalLight*>& directionalLights,
        const Math::Vec3& sceneCenter
    )
    {
        const IDirectionalLight* light = directionalLights.begin()->second;

        glm::vec3 direction = MathUtils::ToGLM(light->GetDirection());
        glm::vec3 lightPos = MathUtils::ToGLM(sceneCenter) - direction * LIGHT_OFFSET;
        glm::mat4 view = glm::lookAt(lightPos, MathUtils::ToGLM(sceneCenter), UP);
            glm::mat4 proj = glm::ortho(
            -light->GetLightOrthographicHalfSize(),
            light->GetLightOrthographicHalfSize(),
            -light->GetLightOrthographicHalfSize(),
            light->GetLightOrthographicHalfSize(),
            light->GetLightNearPlane(),
            light->GetLightFarPlane()
        );

        return proj * view;
    }

    void ShadowRendererOpenGL::PopulateDirectionalLightUniforms(
        ShaderOpenGL& shader,
        const std::unordered_map<int, const IDirectionalLight*>& dirLights
    )
    {
        std::vector<glm::vec3> directions;
        std::vector<glm::vec3> ambient;
        std::vector<glm::vec3> diffuse;
        std::vector<glm::vec3> specular;

        for (const auto& [id, light] : dirLights)
        {
            directions.push_back(MathUtils::ToGLM(light->GetDirection()));
            ambient.push_back(glm::vec3(0.9f)); // TODO: consider adding a method to IDirectionalLight for ambient color
            diffuse.push_back(MathUtils::ToGLM(light->GetDiffuse()));
            specular.push_back(MathUtils::ToGLM(light->GetSpecular()));
        }

        shader.SetUniform("u_numDirLights", static_cast<int>(directions.size()));
        shader.SetUniform("u_dirLightDirections", directions);
        shader.SetUniform("u_dirLightAmbient", ambient);
        shader.SetUniform("u_dirLightDiffuse", diffuse);
        shader.SetUniform("u_dirLightSpecular", specular);
    }

    void ShadowRendererOpenGL::PopulatePointLightUniforms(
        ShaderOpenGL& shader,
        const std::unordered_map<int, const IPointLight*>& pointLights
    )
    {
        std::vector<glm::vec3> positions, ambient, diffuse, specular;
        std::vector<float> intensity, constant, linear, quadratic, farPlane;

        for (const auto& [id, pl] : pointLights)
        {
            positions.push_back(MathUtils::ToGLM(pl->GetPosition()));
            ambient.push_back(MathUtils::ToGLM(pl->GeAmbient()));
            diffuse.push_back(MathUtils::ToGLM(pl->GetDiffuse()));
            specular.push_back(MathUtils::ToGLM(pl->GetSpecular()));

            intensity.push_back(pl->GetIntensity());
            constant.push_back(pl->GetAttenuationConstant());
            linear.push_back(pl->GetAttenuationLinear());
            quadratic.push_back(pl->GetAttenuationQuadratic());
            farPlane.push_back(pl->GetShadowFarPlane());
        }

        shader.SetUniform("u_numPointLights", static_cast<int>(positions.size()));
        shader.SetUniform("u_pointLightPositions", positions);
        shader.SetUniform("u_pointLightAmbient", ambient);
        shader.SetUniform("u_pointLightDiffuse", diffuse);
        shader.SetUniform("u_pointLightSpecular", specular);
        shader.SetUniform("u_pointLightIntensity", intensity);
        shader.SetUniform("u_pointLightConstant", constant);
        shader.SetUniform("u_pointLightLinear", linear);
        shader.SetUniform("u_pointLightQuadratic", quadratic);
        shader.SetUniform("u_pointLightFarPlanes", farPlane);
    }

    void ShadowRendererOpenGL::ConfigurePointShadowPass(
        FrameBufferOpenGL& pointShadowFbo,
        int resolution,
        FaceCullingControlOpenGL& culling,
        int& prevFbo
    )
    {
        culling.EnableFaceCulling(GL_FRONT, GL_CCW);

        glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &prevFbo);

        pointShadowFbo.Bind();
        glViewport(0, 0, resolution, resolution);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_DEPTH_BUFFER_BIT);
    }

    std::vector<glm::mat4> ShadowRendererOpenGL::BuildPointShadowMatrices(
        const glm::vec3& lightPos,
        float nearPlane,
        float farPlane
    )
    {
        const glm::mat4 proj = glm::perspective(glm::radians(CUBEMAP_FOV), CUBEMAP_ASPECT, nearPlane, farPlane);

        std::vector<glm::mat4> matrices(CUBEMAP_FACES);
        for (std::size_t i = 0; i < matrices.size(); ++i)
        {
            matrices[i] = proj * glm::lookAt(lightPos, CUBEMAP_TARGETS[i], CUBEMAP_UPS[i]);
        }

        return matrices;
    }

    void ShadowRendererOpenGL::RenderPointShadowObjects(
        const std::unordered_map<int, IGeometricObject*>& objects,
        const std::unordered_map<int, ITransformable*>& objectTransforms,
        ShaderOpenGL& shader,
        MeshCacheOpenGL& meshCache
    )
    {
        for (const auto& [id, obj] : objects)
        {
            if (!obj || dynamic_cast<const ILightObject*>(obj))
                continue;

            std::unordered_map<int, ITransformable*>::const_iterator transformIt = objectTransforms.find(id);
            if (transformIt == objectTransforms.end() || !transformIt->second)
                continue;

            const GpuMeshOpenGL* mesh = meshCache.TryGet(obj->GetID());
            if (!mesh)
                continue;

            shader.SetUniform("u_model", MathUtils::ToGLM(transformIt->second->GetModelMatrix()));
            glBindVertexArray(mesh->GetVAO());
            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh->GetIndexCount()), GL_UNSIGNED_INT, nullptr);
        }
    }

    void ShadowRendererOpenGL::FinishPointShadowPass(
        int prevFbo,
        FaceCullingControlOpenGL& culling
    )
    {
        glBindFramebuffer(GL_FRAMEBUFFER, prevFbo);
        culling.DisableFaceCulling();
    }
}
