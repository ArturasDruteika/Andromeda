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
    float spacing = 1.05f;
    int pyramidHeight = 10;

    int objectId = 0;

    // Neon-style RGB-only hardcoded palette
    const std::vector<Andromeda::Space::Color> neonColors = {
        {0.0f, 1.0f, 1.0f, 1.0f},     // Electric Cyan
        {1.0f, 0.0f, 1.0f, 1.0f},     // Vivid Magenta
        {0.2f, 1.0f, 0.6f, 1.0f},     // Bright Mint Green
        {0.6f, 0.2f, 1.0f, 1.0f},     // Violet Glow
        {1.0f, 0.2f, 0.6f, 1.0f},     // Hot Pink
        {0.0f, 0.4f, 1.0f, 1.0f},     // Electric Blue
        {0.22f, 1.0f, 0.08f, 1.0f},   // Cyberpunk Green
        {0.56f, 0.0f, 1.0f, 1.0f},    // Cyberpunk Violet
    };


    // Build 10-storey pyramid
    for (int level = 0; level < pyramidHeight; ++level)
    {
        int width = pyramidHeight - level;
        float y = level * spacing;

        for (int row = 0; row < width; ++row)
        {
            for (int col = 0; col < width; ++col)
            {
                // Center the pyramid
                float x = (col - width / 2.0f + 0.5f) * spacing;
                float z = (row - width / 2.0f + 0.5f) * spacing;

                Andromeda::Math::Vec3 pos(x, y, z);

                // Use neon color based on level
                Andromeda::Space::Color color = neonColors[level % neonColors.size()];

                auto* cube = new Andromeda::Rendering::CubeObjectOpenGL(pos, cubeHalfExtent, color);
                app.AddToScene(objectId++, cube);
            }
        }
    }

    // Light source sphere
    float sphereRadius = 0.7f;
    Andromeda::Math::Vec3 spherePosition(15.0f, 10.0f, 10.0f);
    Andromeda::Space::Color sphereColor = { 1.0f, 1.0f, 1.0f, 1.0f };

    auto* lightSphere = new Andromeda::Rendering::SphereObjectOpenGL(spherePosition, sphereRadius, sphereColor);
    lightSphere->SetEmitingLight(true);
    app.AddToScene(objectId++, lightSphere);

    app.RunMainLoop();
    app.DeInit();

    return 0;
}


