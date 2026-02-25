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
#include <unordered_map>
#include <vector>


struct OrbitalBody
{
    int id;
    int parentId;
    float orbitRadius;
    float orbitSpeed;
};

struct SolarSystem
{
    int sunId;
    std::vector<OrbitalBody> planets;
    std::vector<OrbitalBody> moons;
};

struct SolarSystemState
{
    float time = 0.0f;
};

constexpr float kPi = 3.1415926535f;
constexpr float kTwoPi = 2.0f * kPi;
constexpr float kEarthOrbitRadius = 10.0f;
constexpr float kSecondsPerMinute = 60.0f;
constexpr float kEarthDaysPerMinute = 365.0f;
constexpr float kKmPerAu = 149597870.7f;
// Inflate moon distances so they remain visible while preserving relative spacing.
constexpr float kMoonOrbitScale = 80.0f;

float OrbitSpeedFromDays(float periodDays)
{
    const float periodSeconds = kSecondsPerMinute * (periodDays / kEarthDaysPerMinute);
    return kTwoPi / periodSeconds;
}

int AddSphereObject(
    Andromeda::Space::Scene& scene,
    const Andromeda::IMaterial* pMaterial,
    int id,
    float radius,
    const Andromeda::Color& color,
    const Andromeda::Math::Vec3& position
)
{
    Andromeda::Space::Sphere* pSphere = new Andromeda::Space::Sphere(radius, color);
    if (pMaterial)
    {
        pSphere->SetMaterial(pMaterial);
    }

    std::unique_ptr<Andromeda::Space::SceneNode> node =
        std::make_unique<Andromeda::Space::SceneNode>(
            std::make_unique<Andromeda::Transformable>(position)
        );
    node->AddComponent(std::make_unique<Andromeda::Space::ObjectComponent>(id, pSphere));
    scene.AttachNode(std::move(node));

    return id;
}

SolarSystem AddSolarSystem(
    Andromeda::Space::Scene& scene,
    const Andromeda::Space::MaterialLibrary& materialLibrary
)
{
    const Andromeda::IMaterial* pMat = nullptr;
    if (materialLibrary.GetSize() > 0)
    {
        const std::vector<Andromeda::Space::MaterialType> materialTypes =
            materialLibrary.GetAllMaterialTypes();
        if (!materialTypes.empty())
        {
            pMat = materialLibrary.GetMaterialPtr(materialTypes.front());
        }
    }

    SolarSystem system{};
    int nextId = 1001;

    system.sunId = nextId++;
    AddSphereObject(
        scene,
        pMat,
        system.sunId,
        1.5f,
        Andromeda::Color{ 1.0f, 0.8f, 0.2f, 1.0f },
        Andromeda::Math::Vec3{ 0.0f, 0.0f, 0.0f }
    );

    auto addPlanet = [&](int& outId,
                         float radius,
                         const Andromeda::Color& color,
                         float orbitAu,
                         float periodDays)
    {
        const float orbitRadius = kEarthOrbitRadius * orbitAu;
        const float orbitSpeed = OrbitSpeedFromDays(periodDays);
        outId = nextId++;
        AddSphereObject(
            scene,
            pMat,
            outId,
            radius,
            color,
            Andromeda::Math::Vec3{ orbitRadius, 0.0f, 0.0f }
        );
        system.planets.push_back(OrbitalBody{ outId, system.sunId, orbitRadius, orbitSpeed });
    };

    int mercuryId = 0;
    int venusId = 0;
    int earthId = 0;
    int marsId = 0;
    int jupiterId = 0;
    int saturnId = 0;
    int uranusId = 0;
    int neptuneId = 0;

    addPlanet(mercuryId, 0.18f, Andromeda::Color{ 0.6f, 0.6f, 0.6f, 1.0f }, 0.387f, 87.969f);
    addPlanet(venusId, 0.45f, Andromeda::Color{ 0.9f, 0.8f, 0.6f, 1.0f }, 0.723f, 224.701f);
    addPlanet(earthId, 0.5f, Andromeda::Color{ 0.2f, 0.5f, 1.0f, 1.0f }, 1.0f, 365.256f);
    addPlanet(marsId, 0.35f, Andromeda::Color{ 0.8f, 0.3f, 0.2f, 1.0f }, 1.524f, 686.98f);
    addPlanet(jupiterId, 1.0f, Andromeda::Color{ 0.85f, 0.6f, 0.4f, 1.0f }, 5.203f, 4332.59f);
    addPlanet(saturnId, 0.9f, Andromeda::Color{ 0.9f, 0.85f, 0.6f, 1.0f }, 9.537f, 10759.22f);
    addPlanet(uranusId, 0.7f, Andromeda::Color{ 0.6f, 0.85f, 0.9f, 1.0f }, 19.191f, 30688.5f);
    addPlanet(neptuneId, 0.7f, Andromeda::Color{ 0.2f, 0.3f, 0.8f, 1.0f }, 30.07f, 60182.0f);

    auto addMoon = [&](int parentId,
                       float parentOrbitRadius,
                       float radius,
                       const Andromeda::Color& color,
                       float distanceKm,
                       float periodDays)
    {
        const float distanceAu = distanceKm / kKmPerAu;
        const float orbitRadius = distanceAu * kEarthOrbitRadius * kMoonOrbitScale;
        const float orbitSpeed = OrbitSpeedFromDays(periodDays);
        const int moonId = nextId++;
        AddSphereObject(
            scene,
            pMat,
            moonId,
            radius,
            color,
            Andromeda::Math::Vec3{ parentOrbitRadius + orbitRadius, 0.0f, 0.0f }
        );
        system.moons.push_back(OrbitalBody{ moonId, parentId, orbitRadius, orbitSpeed });
    };

    addMoon(earthId, kEarthOrbitRadius, 0.16f, Andromeda::Color{ 0.8f, 0.8f, 0.9f, 1.0f }, 384400.0f, 27.3217f);

    addMoon(marsId, kEarthOrbitRadius * 1.524f, 0.08f, Andromeda::Color{ 0.5f, 0.4f, 0.4f, 1.0f }, 9376.0f, 0.3189f);
    addMoon(marsId, kEarthOrbitRadius * 1.524f, 0.06f, Andromeda::Color{ 0.6f, 0.5f, 0.5f, 1.0f }, 23463.0f, 1.2624f);

    addMoon(jupiterId, kEarthOrbitRadius * 5.203f, 0.16f, Andromeda::Color{ 0.9f, 0.8f, 0.4f, 1.0f }, 421700.0f, 1.769f);
    addMoon(jupiterId, kEarthOrbitRadius * 5.203f, 0.16f, Andromeda::Color{ 0.8f, 0.8f, 0.9f, 1.0f }, 671100.0f, 3.551f);
    addMoon(jupiterId, kEarthOrbitRadius * 5.203f, 0.2f, Andromeda::Color{ 0.7f, 0.7f, 0.7f, 1.0f }, 1070400.0f, 7.155f);
    addMoon(jupiterId, kEarthOrbitRadius * 5.203f, 0.18f, Andromeda::Color{ 0.4f, 0.4f, 0.4f, 1.0f }, 1882700.0f, 16.689f);

    addMoon(saturnId, kEarthOrbitRadius * 9.537f, 0.2f, Andromeda::Color{ 0.9f, 0.7f, 0.4f, 1.0f }, 1221870.0f, 15.945f);
    addMoon(saturnId, kEarthOrbitRadius * 9.537f, 0.12f, Andromeda::Color{ 0.9f, 0.9f, 0.95f, 1.0f }, 237948.0f, 1.37f);
    addMoon(saturnId, kEarthOrbitRadius * 9.537f, 0.14f, Andromeda::Color{ 0.7f, 0.7f, 0.7f, 1.0f }, 527108.0f, 4.518f);
    addMoon(saturnId, kEarthOrbitRadius * 9.537f, 0.14f, Andromeda::Color{ 0.6f, 0.6f, 0.6f, 1.0f }, 3560820.0f, 79.3215f);

    addMoon(uranusId, kEarthOrbitRadius * 19.191f, 0.1f, Andromeda::Color{ 0.7f, 0.7f, 0.75f, 1.0f }, 129390.0f, 1.414f);
    addMoon(uranusId, kEarthOrbitRadius * 19.191f, 0.12f, Andromeda::Color{ 0.7f, 0.75f, 0.8f, 1.0f }, 191020.0f, 2.52f);
    addMoon(uranusId, kEarthOrbitRadius * 19.191f, 0.12f, Andromeda::Color{ 0.6f, 0.65f, 0.7f, 1.0f }, 266300.0f, 4.144f);
    addMoon(uranusId, kEarthOrbitRadius * 19.191f, 0.14f, Andromeda::Color{ 0.75f, 0.75f, 0.8f, 1.0f }, 435910.0f, 8.706f);
    addMoon(uranusId, kEarthOrbitRadius * 19.191f, 0.14f, Andromeda::Color{ 0.65f, 0.65f, 0.7f, 1.0f }, 583520.0f, 13.463f);

    addMoon(neptuneId, kEarthOrbitRadius * 30.07f, 0.16f, Andromeda::Color{ 0.7f, 0.7f, 0.8f, 1.0f }, 354759.0f, 5.877f);
    addMoon(neptuneId, kEarthOrbitRadius * 30.07f, 0.12f, Andromeda::Color{ 0.6f, 0.6f, 0.7f, 1.0f }, 5513818.0f, 360.13f);
    addMoon(neptuneId, kEarthOrbitRadius * 30.07f, 0.1f, Andromeda::Color{ 0.5f, 0.55f, 0.6f, 1.0f }, 117647.0f, 1.122f);

    return system;
}

void UpdateSolarSystem(
    Andromeda::Space::Scene& scene,
    SolarSystemState& state,
    const SolarSystem& system,
    float dt
)
{
    state.time += dt;

    const auto& transforms = scene.GetObjectTransforms();

    auto sunIt = transforms.find(system.sunId);
    if (sunIt == transforms.end() || !sunIt->second)
    {
        return;
    }

    std::unordered_map<int, Andromeda::Math::Vec3> positions;
    const Andromeda::Math::Vec3 sunPos = sunIt->second->GetPosition();
    positions[system.sunId] = sunPos;

    for (const auto& planet : system.planets)
    {
        auto planetIt = transforms.find(planet.id);
        if (planetIt == transforms.end() || !planetIt->second)
        {
            continue;
        }

        const Andromeda::Math::Vec3 parentPos = positions[planet.parentId];
        const float angle = state.time * planet.orbitSpeed;
        const Andromeda::Math::Vec3 planetPos{
            parentPos[0] + std::cos(angle) * planet.orbitRadius,
            parentPos[1],
            parentPos[2] + std::sin(angle) * planet.orbitRadius
        };
        planetIt->second->SetPosition(planetPos);
        positions[planet.id] = planetPos;
    }

    for (const auto& moon : system.moons)
    {
        auto moonIt = transforms.find(moon.id);
        if (moonIt == transforms.end() || !moonIt->second)
        {
            continue;
        }

        auto parentPosIt = positions.find(moon.parentId);
        if (parentPosIt == positions.end())
        {
            continue;
        }
        const Andromeda::Math::Vec3 parentPos = parentPosIt->second;
        const float angle = state.time * moon.orbitSpeed;
        const Andromeda::Math::Vec3 moonPos{
            parentPos[0] + std::cos(angle) * moon.orbitRadius,
            parentPos[1],
            parentPos[2] + std::sin(angle) * moon.orbitRadius
        };
        moonIt->second->SetPosition(moonPos);
    }
}


int main(void)
{
    unsigned int width = 800;
    unsigned int height = 600;
    std::string title = "Andromeda - Solar System Simulation";

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
        Andromeda::Math::Vec3{ 0.0f, 40.0f, 220.0f }
    );
    pScene->SetActiveCamera(pCamera);
    pScene->SetBackgroundColor(Andromeda::Math::Vec4{ 0.0f, 0.0f, 0.0f, 1.0f });

    const SolarSystem solarSystem = AddSolarSystem(*pScene, materialLibrary);

    SolarSystemState solarSystemState{};
    Andromeda::ISceneUpdateHooks::Handle handle = pScene->AddUpdateCallback(
        [pScene, solarSystemState, solarSystem](float dt) mutable
        {
            UpdateSolarSystem(*pScene, solarSystemState, solarSystem, dt);
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
