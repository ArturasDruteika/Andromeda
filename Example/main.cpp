#include "Application.hpp"
#include "LinearAlgebraDataTypes.hpp"
#include "Sphere.hpp"


int main(void)
{
	float sphereRadius = 1.0f;
	Andromeda::Math::Vec3 spherePosition(0.0f, 0.0f, 0.0f);
    Andromeda::Space::Sphere sphere = Andromeda::Space::Sphere(spherePosition, Andromeda::Space::Color(1.0f, 0.0f, 0.0f, 1.0f));

    Andromeda::EngineCore::Application app;
    app.Init();
    app.RunMainLoop();
    app.DeInit();

    return 0;
}