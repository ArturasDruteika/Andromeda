#include "Application.hpp"
#include "LinearAlgebraDataTypes.hpp"
#include "Sphere.hpp"
#include "SphereObjectOpenGL.hpp"


int main(void)
{
    Andromeda::EngineCore::Application app;
    app.Init();

	float sphereRadius = 1.0f;
	Andromeda::Math::Vec3 spherePosition(0.0f, 0.0f, 0.0f);
    //Andromeda::Space::Sphere sphere = Andromeda::Space::Sphere(spherePosition, Andromeda::Space::Color(1.0f, 0.0f, 0.0f, 1.0f));
	Andromeda::Rendering::SphereObjectOpenGL* sphereObjectOpenGL = new Andromeda::Rendering::SphereObjectOpenGL(sphereRadius, Andromeda::Space::Color(1.0f, 0.0f, 0.0f, 1.0f));
	app.AddToScene(0, sphereObjectOpenGL);

    app.RunMainLoop();
    app.DeInit();

    return 0;
}