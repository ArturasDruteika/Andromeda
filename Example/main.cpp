#include "Application.hpp"
#include "LinearAlgebraDataTypes.hpp"
#include "Sphere.hpp"
#include "Cube.hpp"
#include "SphereObjectOpenGL.hpp"
#include "CubeObjectOpenGL.hpp"
#include "Constants.hpp"


int main(void)
{
    Andromeda::EngineCore::Application app;
    app.Init();

	float cubeHalfExtent = 0.5f;
	float radius = 0.7f;

	Andromeda::Math::Vec3 cubePosition(0.0f, 0.0f, 0.0f);
	Andromeda::Math::Vec3 spherePosition(-4.0f, -2.0f, -2.5f);

	Andromeda::Space::Color cubeColor = { 0.2f, 1.0f, 0.4f, 1.0f };
	Andromeda::Space::Color sphereColor = { 1.0f, 1.0f, 1.0f, 1.0f };

	Andromeda::Space::Cube cube = Andromeda::Space::Cube(cubePosition, cubeHalfExtent, Andromeda::Space::Color(1.0f, 0.0f, 0.0f, 1.0f));
	Andromeda::Space::Sphere sphere = Andromeda::Space::Sphere(spherePosition, radius, Andromeda::Space::Color(1.0f, 0.0f, 0.0f, 1.0f));

	Andromeda::Rendering::CubeObjectOpenGL* cubeObjectOpenGL = new Andromeda::Rendering::CubeObjectOpenGL(cubePosition, cubeHalfExtent, cubeColor);
	Andromeda::Rendering::SphereObjectOpenGL* sphereObjectOpenGL = new Andromeda::Rendering::SphereObjectOpenGL(spherePosition, radius, sphereColor);
	sphereObjectOpenGL->SetEmitingLight(true);

	app.AddToScene(0, cubeObjectOpenGL);
	app.AddToScene(1, sphereObjectOpenGL);

    app.RunMainLoop();
    app.DeInit();

    return 0;
}