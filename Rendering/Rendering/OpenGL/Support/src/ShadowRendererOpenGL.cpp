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
    void ShadowRendererOpenGL::RenderDirectionalShadowMap(
        const std::unordered_map<int, IGeometricObject*>& objects,
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

            const GpuMeshOpenGL* mesh = meshCache.TryGet(obj->GetID());
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
        culling.DisableFaceCulling();
    }

    void ShadowRendererOpenGL::RenderPointShadowCube(
        const std::unordered_map<int, IGeometricObject*>& objects,
        FrameBufferOpenGL& pointShadowFbo,
        int resolution,
        const glm::vec3& lightPos,
        float nearPlane,
        float farPlane,
        ShaderManager& shaderManager,
        MeshCacheOpenGL& meshCache,
        FaceCullingControlOpenGL& culling
    )
    {
        culling.EnableFaceCulling(GL_FRONT, GL_CCW);

        int prevFBO;
        glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &prevFBO);

        pointShadowFbo.Bind();
        glViewport(0, 0, resolution, resolution);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_DEPTH_BUFFER_BIT);

        ShaderOpenGL* shader = shaderManager.GetShader(ShaderOpenGLTypes::PointShadowCubeMap);
        shader->Bind();

        const glm::mat4 proj = glm::perspective(glm::radians(90.0f), 1.0f, nearPlane, farPlane);

        std::vector<glm::vec3> ups{
            {0, -1, 0},
            {0, -1, 0},
            {0,  0, 1},
            {0,  0,-1},
            {0, -1, 0},
            {0, -1, 0}
        };

        std::vector<glm::vec3> targets{
            lightPos + glm::vec3(1, 0, 0),
            lightPos + glm::vec3(-1, 0, 0),
            lightPos + glm::vec3(0, 1, 0),
            lightPos + glm::vec3(0,-1, 0),
            lightPos + glm::vec3(0, 0, 1),
            lightPos + glm::vec3(0, 0,-1)
        };

        std::vector<glm::mat4> matrices(6);
        for (std::size_t i = 0; i < matrices.size(); ++i)
        {
            matrices[i] = proj * glm::lookAt(lightPos, targets[i], ups[i]);
        }

        shader->SetUniform("u_shadowMatrices[0]", matrices);
        shader->SetUniform("u_lightPos", lightPos);
        shader->SetUniform("u_farPlane", farPlane);

        for (const auto& [id, obj] : objects)
        {
            if (!obj)
            {
                continue;
            }

            if (dynamic_cast<const ILightObject*>(obj))
            {
                continue;
            }

            const GpuMeshOpenGL* mesh = meshCache.TryGet(obj->GetID());
            if (!mesh)
            {
                continue;
            }

            shader->SetUniform("u_model", MathUtils::ToGLM(obj->GetModelMatrix()));
            glBindVertexArray(mesh->GetVAO());
            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh->GetIndexCount()), GL_UNSIGNED_INT, nullptr);
        }

        shader->UnBind();
        glBindFramebuffer(GL_FRAMEBUFFER, prevFBO);
        culling.DisableFaceCulling();
    }

    glm::mat4 ShadowRendererOpenGL::ComputeLightSpaceMatrix(
        const std::unordered_map<int, const IDirectionalLight*>& directionalLights,
        const Math::Vec3& sceneCenter
    )
    {
        const IDirectionalLight* light = directionalLights.begin()->second;

        glm::vec3 direction = MathUtils::ToGLM(light->GetDirection());
        glm::vec3 up(0.0f, 1.0f, 0.0f);

        glm::vec3 lightPos = MathUtils::ToGLM(sceneCenter) - direction * 20.0f;

        glm::mat4 view = glm::lookAt(lightPos, MathUtils::ToGLM(sceneCenter), up);

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
            ambient.push_back(glm::vec3(0.9f));
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
}
