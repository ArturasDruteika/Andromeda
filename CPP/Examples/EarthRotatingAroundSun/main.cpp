#include "Andromeda/Application/IApplication.hpp"
#include "Andromeda/Space/Scene/ISceneUpdateHooks.hpp"
#include "Andromeda/Space/Transformations/ITransformable.hpp"
#include "Space/Objects/include/Sphere.hpp"
#include "Space/Scene/include/Scene.hpp"
#include "Space/SceneGraph/include/SceneNode.hpp"
#include "Space/SceneGraph/include/ObjectComponent.hpp"
#include "Space/Transformations/include/Transformable.hpp"
#include "Space/Camera/include/Camera.hpp"
#include "Space/Materials/include/MaterialsLibrary.hpp"

#include "spdlog/spdlog.h"

#include <cmath>
#include <filesystem>
#include <string>
#include <vector>


struct SolarSystemIds
{
    int sunId;
    int earthId;
    int moonId;
};

struct SolarSystemState
{
    float time = 0.0f;
    float earthOrbitRadius = 6.0f;
    float earthOrbitSpeed = 0.6f;
    float moonOrbitRadius = 2.0f;
    float moonOrbitSpeed = 1.8f;
};

SolarSystemIds AddSunAndEarth(
    Andromeda::Space::Scene& scene,
    const Andromeda::Space::MaterialLibrary& materialLibrary
)
{
    const int sunId = 1001;
    const int earthId = 1002;
    const int moonId = 1003;

    Andromeda::Space::Sphere* pSun = new Andromeda::Space::Sphere(
        1.5f,
        Andromeda::Color{ 1.0f, 0.8f, 0.2f, 1.0f }
    );
    Andromeda::Space::Sphere* pEarth = new Andromeda::Space::Sphere(
        0.6f,
        Andromeda::Color{ 0.2f, 0.5f, 1.0f, 1.0f }
    );
    Andromeda::Space::Sphere* pMoon = new Andromeda::Space::Sphere(
        0.25f,
        Andromeda::Color{ 0.8f, 0.8f, 0.9f, 1.0f }
    );

    if (materialLibrary.GetSize() > 0)
    {
        const std::vector<Andromeda::Space::MaterialType> materialTypes =
            materialLibrary.GetAllMaterialTypes();
        if (!materialTypes.empty())
        {
            const Andromeda::IMaterial* pMat =
                materialLibrary.GetMaterialPtr(materialTypes.front());
            if (pMat)
            {
                pSun->SetMaterial(pMat);
                pEarth->SetMaterial(pMat);
                pMoon->SetMaterial(pMat);
            }
        }
    }

    {
        std::unique_ptr<Andromeda::Space::SceneNode> sunNode =
            std::make_unique<Andromeda::Space::SceneNode>(
                std::make_unique<Andromeda::Transformable>(Andromeda::Math::Vec3{ 0.0f, 0.0f, 0.0f })
            );
        sunNode->AddComponent(std::make_unique<Andromeda::Space::ObjectComponent>(sunId, pSun));
        scene.AttachNode(std::move(sunNode));
    }

    {
        std::unique_ptr<Andromeda::Space::SceneNode> earthNode =
            std::make_unique<Andromeda::Space::SceneNode>(
                std::make_unique<Andromeda::Transformable>(Andromeda::Math::Vec3{ 6.0f, 0.0f, 0.0f })
            );
        earthNode->AddComponent(std::make_unique<Andromeda::Space::ObjectComponent>(earthId, pEarth));
        scene.AttachNode(std::move(earthNode));
    }

    {
        std::unique_ptr<Andromeda::Space::SceneNode> moonNode =
            std::make_unique<Andromeda::Space::SceneNode>(
                std::make_unique<Andromeda::Transformable>(Andromeda::Math::Vec3{ 8.0f, 0.0f, 0.0f })
            );
        moonNode->AddComponent(std::make_unique<Andromeda::Space::ObjectComponent>(moonId, pMoon));
        scene.AttachNode(std::move(moonNode));
    }

    return SolarSystemIds{ sunId, earthId, moonId };
}

void UpdateSolarSystem(
    Andromeda::Space::Scene& scene,
    SolarSystemState& state,
    const SolarSystemIds& solarSystemIds,
    float dt
)
{
    state.time += dt;

    const auto& transforms = scene.GetObjectTransforms();

    auto sunIt = transforms.find(solarSystemIds.sunId);
    auto earthIt = transforms.find(solarSystemIds.earthId);
    auto moonIt = transforms.find(solarSystemIds.moonId);
    if (sunIt == transforms.end() || earthIt == transforms.end() || moonIt == transforms.end())
    {
        return;
    }

    Andromeda::ITransformable* sunTransform = sunIt->second;
    Andromeda::ITransformable* earthTransform = earthIt->second;
    Andromeda::ITransformable* moonTransform = moonIt->second;
    if (!sunTransform || !earthTransform || !moonTransform)
    {
        return;
    }

    const Andromeda::Math::Vec3 sunPos = sunTransform->GetPosition();

    const float earthAngle = state.time * state.earthOrbitSpeed;
    const Andromeda::Math::Vec3 earthPos{
        sunPos[0] + std::cos(earthAngle) * state.earthOrbitRadius,
        sunPos[1],
        sunPos[2] + std::sin(earthAngle) * state.earthOrbitRadius
    };

    earthTransform->SetPosition(earthPos);

    const float moonAngle = state.time * state.moonOrbitSpeed;
    const Andromeda::Math::Vec3 moonPos{
        earthPos[0] + std::cos(moonAngle) * state.moonOrbitRadius,
        earthPos[1],
        earthPos[2] + std::sin(moonAngle) * state.moonOrbitRadius
    };

    moonTransform->SetPosition(moonPos);
}


int main(void)
{
    unsigned int width = 800;
    unsigned int height = 600;
    std::string title = "Andromeda - EarthRotatingAroundSun";

    // Load materials once and reuse
    Andromeda::Space::MaterialLibrary materialLibrary(
        std::filesystem::path("material_properties/material_properties.json")
    );

    if (materialLibrary.GetSize() == 0)
    {
        spdlog::warn("No materials loaded from assets/materials.json; spheres will fall back to having no materials.");
    }

    Andromeda::Space::Scene* pScene = new Andromeda::Space::Scene();
    Andromeda::Space::Camera* pCamera = new Andromeda::Space::Camera(
        Andromeda::Math::Vec3{ 0.0f, 0.0f, 10.0f }
    );
    pScene->SetActiveCamera(pCamera);
    pScene->SetBackgroundColor(Andromeda::Math::Vec4{ 0.0f, 0.0f, 0.0f, 1.0f });

    const SolarSystemIds solarSystemIds = AddSunAndEarth(*pScene, materialLibrary);

    SolarSystemState solarSystemState{};
    Andromeda::ISceneUpdateHooks::Handle handle = pScene->AddUpdateCallback(
        [pScene, solarSystemState, solarSystemIds](float dt) mutable
        {
            UpdateSolarSystem(*pScene, solarSystemState, solarSystemIds, dt);
        }
    );

    std::unique_ptr<Andromeda::IApplication> pApp =
        Andromeda::CreateApp(Andromeda::GraphicsBackend::OpenGL);
    if (!pApp->Init(width, height, title))
    {
        spdlog::error("Failed to initialize Application.");
        return -1;
    }

    pApp->SetScene(pScene);
    Andromeda::IRenderer* pRenderer = pApp->GetRenderer();
    pRenderer->SetIlluminationMode(false);
    pApp->Run();

    return 0;
}
