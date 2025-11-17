//#include "Application.hpp"
//#include "LinearAlgebraDataTypes.hpp"
//#include "SphereObjectOpenGL.hpp"
//#include "SkyroomOpenGL.hpp"
//#include "CubeObjectOpenGL.hpp"
//#include "Constants.hpp"
//#include "DirectionalLight.hpp"
//#include "PointLight.hpp"
//#include "LuminousBehavior.hpp"
//#include "NonLuminousBehavior.hpp"
//#include "MaterialsLibrary.hpp"
//#include "Materials.hpp"
//#include "MaterialTypes.hpp"
//#include "LinearAlgebraOperations.hpp"
//#include "GraphicsBackend.hpp"
#include "IEngine.hpp"
//#include "Engine.hpp"
//#include "glm/glm.hpp"


int main(void)
{
	std::unique_ptr<Andromeda::IEngine> pEngine = Andromeda::CreateEngine(Andromeda::GraphicsBackend::OpenGL);


	return 0;
}



//int main (void)
//{ 
 //   Andromeda::EngineCore::Application app;
 //   app.Init();

 //   Andromeda::PhysicalProperties::MaterialLibrary materialsLib("material_properties/material_properties.json");

 //   float cubeHalfExtent = 0.5f;
 //   float spacing = 1.05f;
 //   int pyramidHeight = 10;

 //   int objectId = 0;

 //   // Collect available materials
 //   std::vector<Andromeda::PhysicalProperties::MaterialType> materialTypes;
 //   for (int i = 0; i < static_cast<int>(Andromeda::PhysicalProperties::MaterialType::Count); ++i)
 //   {
 //       Andromeda::PhysicalProperties::MaterialType type = static_cast<Andromeda::PhysicalProperties::MaterialType>(i);
 //       if (type != Andromeda::PhysicalProperties::MaterialType::None && materialsLib.Has(type))
 //       {
 //           materialTypes.push_back(type);
 //       }
 //   }

 //   size_t numMaterials = materialTypes.size();
 //   if (numMaterials == 0)
 //   {
 //       std::cerr << "No materials found in material library. Aborting." << std::endl;
 //       return -1;
 //   }

 //   // Build material-based pyramid
 //   for (int level = 0; level < pyramidHeight; ++level)
 //   {
 //       int width = pyramidHeight - level;
 //       float y = level * spacing;

 //       for (int row = 0; row < width; ++row)
 //       {
 //           for (int col = 0; col < width; ++col)
 //           {
 //               float x = (col - width / 2.0f + 0.5f) * spacing;
 //               float z = (row - width / 2.0f + 0.5f) * spacing;
 //               Andromeda::Math::Vec3 pos(x, y, z);

 //               // Select material in cyclic order
 //               Andromeda::PhysicalProperties::MaterialType materialType = materialTypes[objectId % numMaterials];
 //               Andromeda::PhysicalProperties::Material material = materialsLib.GetMaterial(materialType);

 //               Andromeda::PhysicalProperties::Color color(
 //                   material.GetDiffuse()[0],
 //                   material.GetDiffuse()[1],
 //                   material.GetDiffuse()[2],
 //                   1.0f
 //               );

 //               Andromeda::Rendering::CubeObjectOpenGL* pCube = new Andromeda::Rendering::CubeObjectOpenGL(pos, cubeHalfExtent, color);
 //               Andromeda::PhysicalProperties::NonLuminousBehavior* nlBehavior = new Andromeda::PhysicalProperties::NonLuminousBehavior(material);
 //               pCube->SetLuminousBehavior(nlBehavior); // if your class supports material application
 //               app.AddToScene(objectId++, pCube);
 //           }
 //       }
 //   }

 //   // Light source sphere
 //   float sphereRadius = 0.7f;
 //   Andromeda::Math::Vec3 spherePosition(10.0f, 5.0f, -5.0f);
 //   Andromeda::PhysicalProperties::Color sphereColor(1.0f, 1.0f, 1.0f, 1.0f);

 //   Andromeda::PhysicalProperties::PointLight* pPointLight = new Andromeda::PhysicalProperties::PointLight(
 //       Andromeda::Math::Vec3(spherePosition[0], spherePosition[1], spherePosition[2]),                 // position
 //       Andromeda::Math::Vec3(sphereColor.r, sphereColor.g, sphereColor.b),                    // color
 //       1.0f,                           // intensity
 //       Andromeda::Math::Vec3(1.0f, 1.0f, 1.0f),    // ambient
 //       Andromeda::Math::Vec3(1.0f, 1.0f, 1.0f),    // diffuse
 //       Andromeda::Math::Vec3(1.0f, 1.0f, 1.0f),    // specular
 //       1.0f,                           // k_c (constant attenuation)
 //       0.0f,                           // k_l (linear attenuation)
 //       0.0f,                           // k_q (quadratic attenuation)
 //       0.1f,                           // near (shadow z range)
 //       1000.0f                         // far (shadow z range)
 //   );

 //   Andromeda::Rendering::SphereObjectOpenGL* pSphere = new Andromeda::Rendering::SphereObjectOpenGL(
 //       spherePosition,
 //       sphereRadius,
 //       sphereColor
 //   );
 //   pSphere->SetLuminousBehavior(pPointLight);

 //   Andromeda::Math::Vec3 directionalLightDirection(2.0f, -1.0f, -4.0f);
 //   Andromeda::PhysicalProperties::DirectionalLight* pDirectionalLight = new Andromeda::PhysicalProperties::DirectionalLight(
 //       directionalLightDirection,
 //       Andromeda::Math::Vec3(1.0f, 1.0f, 1.0f), // Color
 //       1.0f, // Intensity
 //       Andromeda::Math::Vec3(0.1f, 0.1f, 0.1f), // Ambient
 //       Andromeda::Math::Vec3(0.4f, 0.4f, 0.4f), // Diffuse
 //       Andromeda::Math::Vec3(0.4f, 0.4f, 0.4f) // Specular
	//);

 //   Andromeda::PhysicalProperties::MaterialType materialType = materialTypes[5];
 //   Andromeda::PhysicalProperties::Material material = materialsLib.GetMaterial(materialType);

 //   Andromeda::Rendering::SkyroomOpenGL* pSkyroom = new Andromeda::Rendering::SkyroomOpenGL(
 //       Andromeda::Math::Vec3(0.0f, 0.0f, 0.0f),
 //       50.0f,
 //       Andromeda::PhysicalProperties::Color(0.5f, 0.7f, 0.9f, 1.0f) // Light blue
	//);

 //   Andromeda::PhysicalProperties::NonLuminousBehavior* nlBehavior = new Andromeda::PhysicalProperties::NonLuminousBehavior(material);
	//pSkyroom->SetLuminousBehavior(nlBehavior);

 //   app.AddToScene(objectId++, pDirectionalLight);
 //   app.AddToScene(objectId++, pSphere);
 //   app.AddToScene(objectId++, pSkyroom);

 //   app.RunMainLoop();
 //   app.DeInit();

 //	  return 0;
//}
