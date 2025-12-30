#include "Andromeda/Engine/IEngine.hpp"
#include "Andromeda/Platform/IPlatform.hpp"
#include "Andromeda/Application/IApplication.hpp"
#include "Space/Objects/include/Sphere.hpp"
#include "Space/Objects/include/Cube.hpp"
#include "Space/Scene/include/Scene.hpp"
#include "Space/Camera/include/Camera.hpp"

#include "spdlog/spdlog.h"

#include <random>


int main(void)
{
	unsigned int width = 800;
	unsigned int height = 600;
	std::string title = "Andromeda";

	Andromeda::Space::Scene* pScene = new Andromeda::Space::Scene();
	Andromeda::Space::Camera* pCamera = new Andromeda::Space::Camera(Andromeda::Math::Vec3{ 0.0f, 0.0f, 10.0f });
	pScene->SetActiveCamera(pCamera);
	pScene->SetBackgroundColor(Andromeda::Math::Vec4{ 0.0f, 1.0f, 1.0f, 1.0f });

	Andromeda::Space::Sphere* pSphere = new Andromeda::Space::Sphere(
		1.0f, 
		Andromeda::Math::Vec3{ 0.0f, 0.0f, 0.0f }, 
		Andromeda::Color{ 0.8f, 0.2f, 0.2f, 1.0f }
	);
	pScene->AddObject(0, pSphere);

	const int kSphereCount = 1000;
	const float kHalfExtent = 100.0f;

	std::mt19937 rng(1337);
	std::uniform_real_distribution<float> dist(-kHalfExtent, kHalfExtent);

	for (int i = 1; i < kSphereCount; ++i)
	{
		Andromeda::Math::Vec3 pos{
			dist(rng),
			dist(rng),
			dist(rng)
		};

		// Radius 1.0, white color (adjust as you want)
		Andromeda::Space::Sphere* pSphere = new Andromeda::Space::Sphere(
			1.0f,
			pos,
			Andromeda::Color{ 0.2f, 0.2f, 0.8f, 0.0f }
		);

		pScene->AddObject(i, pSphere);
	}

	std::unique_ptr<Andromeda::IApplication> pApp = Andromeda::CreateApp(Andromeda::GraphicsBackend::OpenGL);
	if (!pApp->Init(width, height, title))
	{
		spdlog::error("Failed to initialize Application.");
		return -1;
	}

	pApp->SetScene(pScene);
	pApp->Run();

	return 0;
}