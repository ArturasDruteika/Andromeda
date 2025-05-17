#include "Application.hpp"
#include "LinearAlgebraDataTypes.hpp"
#include "Sphere.hpp"
#include "Cube.hpp"
#include "SphereObjectOpenGL.hpp"
#include "CubeObjectOpenGL.hpp"


int main(void)
{
    Andromeda::EngineCore::Application app;
    app.Init();

	float cubeHalfExtent = 0.5f;
	Andromeda::Math::Vec3 cubePosition(0.0f, 0.0f, 0.0f);
	Andromeda::Space::Cube cube = Andromeda::Space::Cube(cubePosition, cubeHalfExtent, Andromeda::Space::Color(1.0f, 0.0f, 0.0f, 1.0f));

	Andromeda::Rendering::CubeObjectOpenGL* cubeObjectOpenGL = new Andromeda::Rendering::CubeObjectOpenGL(cubePosition, cubeHalfExtent, Andromeda::Space::Color(0.2f, 1.0f, 0.4f, 1.0f));
	app.AddToScene(0, cubeObjectOpenGL);

    app.RunMainLoop();
    app.DeInit();

    return 0;
}