#include "Application.hpp"
#include "LinearAlgebraDataTypes.hpp"
#include "Sphere.hpp"
#include "Cube.hpp"
#include "SphereObjectOpenGL.hpp"
#include "CubeObjectOpenGL.hpp"
#include "Constants.hpp"
#include "PointLight.hpp"
#include "LuminousBehavior.hpp"
#include "NonLuminousBehavior.hpp"
#include "MaterialsLibrary.hpp"
#include "Materials.hpp"
#include "MaterialTypes.hpp"
#include "glm/glm.hpp"


int main(void)
{
    Andromeda::EngineCore::Application app;
    app.Init();

    Andromeda::Rendering::MaterialLibrary materialsLib("material_properties/material_properties.json");

    float cubeHalfExtent = 0.5f;
    float spacing = 1.05f;
    int pyramidHeight = 10;

    int objectId = 0;

    // Collect available materials
    std::vector<Andromeda::Rendering::MaterialType> materialTypes;
    for (int i = 0; i < static_cast<int>(Andromeda::Rendering::MaterialType::Count); ++i)
    {
        Andromeda::Rendering::MaterialType type = static_cast<Andromeda::Rendering::MaterialType>(i);
        if (type != Andromeda::Rendering::MaterialType::None && materialsLib.Has(type))
        {
            materialTypes.push_back(type);
        }
    }

    size_t numMaterials = materialTypes.size();
    if (numMaterials == 0)
    {
        std::cerr << "No materials found in material library. Aborting." << std::endl;
        return -1;
    }

    // Build material-based pyramid
    for (int level = 0; level < pyramidHeight; ++level)
    {
        int width = pyramidHeight - level;
        float y = level * spacing;

        for (int row = 0; row < width; ++row)
        {
            for (int col = 0; col < width; ++col)
            {
                float x = (col - width / 2.0f + 0.5f) * spacing;
                float z = (row - width / 2.0f + 0.5f) * spacing;
                Andromeda::Math::Vec3 pos(x, y, z);

                // Select material in cyclic order
                Andromeda::Rendering::MaterialType materialType = materialTypes[objectId % numMaterials];
                Andromeda::Rendering::Material material = materialsLib.GetMaterial(materialType);

                Andromeda::Space::Color color(
                    material.GetDiffuse()[0],
                    material.GetDiffuse()[1],
                    material.GetDiffuse()[2],
                    1.0f
                );

                Andromeda::Rendering::CubeObjectOpenGL* cube = new Andromeda::Rendering::CubeObjectOpenGL(pos, cubeHalfExtent, color);
                Andromeda::Rendering::NonLuminousBehavior* nlBehavior = new Andromeda::Rendering::NonLuminousBehavior(material);
                cube->SetLuminousBehavior(nlBehavior); // if your class supports material application
                app.AddToScene(objectId++, cube);
            }
        }
    }

    // Light source sphere
    float sphereRadius = 0.7f;
    Andromeda::Math::Vec3 spherePosition(10.0f, 5.0f, 5.0f);
    Andromeda::Space::Color sphereColor(1.0f, 1.0f, 1.0f, 1.0f);

    Andromeda::Rendering::SphereObjectOpenGL* lightSphere = new Andromeda::Rendering::SphereObjectOpenGL(spherePosition, sphereRadius, sphereColor);

    Andromeda::Rendering::PointLight* pPointLight = new Andromeda::Rendering::PointLight(
        glm::vec3(spherePosition[0], spherePosition[1], spherePosition[2]),
        glm::vec3(sphereColor.r, sphereColor.g, sphereColor.b)
    );

    Andromeda::Rendering::LuminousBehavior* lumBehavior = new Andromeda::Rendering::LuminousBehavior(pPointLight);
    lightSphere->SetLuminousBehavior(lumBehavior);
    app.AddToScene(objectId++, lightSphere);

    app.RunMainLoop();
    app.DeInit();

    return 0;
}
