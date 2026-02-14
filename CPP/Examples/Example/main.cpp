#include "Andromeda/Application/IApplication.hpp"
#include "Space/Objects/include/Sphere.hpp"
#include "Space/Objects/include/Cube.hpp"
#include "Space/Scene/include/Scene.hpp"
#include "Space/SceneGraph/include/SceneNode.hpp"
#include "Space/SceneGraph/include/ObjectComponent.hpp"
#include "Space/SceneGraph/include/LightComponent.hpp"
#include "Space/Transformations/include/Transformable.hpp"
#include "Space/Camera/include/Camera.hpp"
#include "Space/Materials/include/MaterialsLibrary.hpp"
#include "Space/Light/include/DirectionalLight.hpp"

#include "spdlog/spdlog.h"

#include <random>


void PopulateSceneWithDummyObjects(
	Andromeda::Space::Scene& scene,
	const Andromeda::Space::MaterialLibrary& materialLibrary
)
{
	// Precompute available material types for random selection
	std::vector<Andromeda::Space::MaterialType> materialTypes = materialLibrary.GetAllMaterialTypes();
	if (materialTypes.empty())
	{
		spdlog::warn("PopulateSceneWithDummyObjects - MaterialLibrary is empty; spheres will have no materials set.");
	}

	std::mt19937 rng(1337);
	std::uniform_real_distribution<float> dist(-100.0f, 100.0f);
	std::uniform_real_distribution<float> colorDist(0.1f, 0.9f);

	std::uniform_int_distribution<size_t> materialDist(
		0,
		materialTypes.empty() ? 0 : materialTypes.size() - 1
	);

	// Sun
	Andromeda::Space::DirectionalLight* pSun = new Andromeda::Space::DirectionalLight(
		Andromeda::Math::Vec3{ 10.0f, 10.0f, 10.0f },
		Andromeda::Math::Vec3{ 1.0f, 1.0f, 1.0f },
		1.0f
	);

	{
		std::unique_ptr<Andromeda::Space::SceneNode> sunNode =
			std::make_unique<Andromeda::Space::SceneNode>(
			std::make_unique<Andromeda::Transformable>(Andromeda::Math::Vec3{ 10.0f, 10.0f, 10.0f })
		);
		sunNode->AddComponent(std::make_unique<Andromeda::Space::LightComponent>(0, pSun));
		scene.AttachNode(std::move(sunNode));
	}


	Andromeda::Space::Sphere* pCenterSphere = new Andromeda::Space::Sphere(
		0.1f,
		Andromeda::Color{ 0.8f, 0.2f, 0.2f, 1.0f }
	);
	{
		std::unique_ptr<Andromeda::Space::SceneNode> centerNode =
			std::make_unique<Andromeda::Space::SceneNode>(
			std::make_unique<Andromeda::Transformable>(Andromeda::Math::Vec3{ 0.0f, 0.0f, 0.0f })
		);
		centerNode->AddComponent(std::make_unique<Andromeda::Space::ObjectComponent>(1, pCenterSphere));
		scene.AttachNode(std::move(centerNode));
	}

	if (!materialTypes.empty())
	{
		Andromeda::Space::MaterialType sphereCenterMatType = materialTypes[materialDist(rng)];
		const Andromeda::IMaterial* pSphereCenterMat =
			materialLibrary.GetMaterialPtr(sphereCenterMatType);
		if (pSphereCenterMat)
		{
			pCenterSphere->SetMaterial(pSphereCenterMat);
		}
	}

	const int kSphereCount = 1000;

	for (int i = 2; i < kSphereCount; ++i)
	{
		Andromeda::Math::Vec3 pos{
			dist(rng),
			dist(rng),
			dist(rng)
		};

		Andromeda::Color color{
			colorDist(rng),
			colorDist(rng),
			colorDist(rng),
			1.0f
		};

		Andromeda::Space::Sphere* pSphere = new Andromeda::Space::Sphere(
			1.0f,
			color
		);

		// Assign random material
		if (!materialTypes.empty())
		{
			Andromeda::Space::MaterialType matType = materialTypes[materialDist(rng)];
			const Andromeda::IMaterial* pMat = materialLibrary.GetMaterialPtr(matType);
			if (pMat)
			{
				pSphere->SetMaterial(pMat);
			}
		}

		{
			std::unique_ptr<Andromeda::Space::SceneNode> sphereNode =
				std::make_unique<Andromeda::Space::SceneNode>(
				std::make_unique<Andromeda::Transformable>(pos)
			);
			sphereNode->AddComponent(std::make_unique<Andromeda::Space::ObjectComponent>(i, pSphere));
			scene.AttachNode(std::move(sphereNode));
		}
	}
}


int main(void)
{
	unsigned int width = 800;
	unsigned int height = 600;
	std::string title = "Andromeda";

	// Load materials once and reuse
	// Adjust the path to your actual JSON file location
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

	PopulateSceneWithDummyObjects(*pScene, materialLibrary);

	std::unique_ptr<Andromeda::IApplication> pApp =
		Andromeda::CreateApp(Andromeda::GraphicsBackend::OpenGL);
	if (!pApp->Init(width, height, title))
	{
		spdlog::error("Failed to initialize Application.");
		return -1;
	}

	pApp->SetScene(pScene);
	Andromeda::IRenderer* pRenderer = pApp->GetRenderer();
	pRenderer->SetIlluminationMode(true);
	pApp->Run();

	return 0;
}
