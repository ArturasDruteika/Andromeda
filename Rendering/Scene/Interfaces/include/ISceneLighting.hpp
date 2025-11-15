#ifndef ENVIRONMENT__I_SCENE_LIGHTING__HPP
#define ENVIRONMENT__I_SCENE_LIGHTING__HPP


#include "../../../MacroExports/include/MacroExports.hpp"
#include "pch.hpp"
#include "DirectionalLight.hpp"
#include "PointLight.hpp"
#include "../../../RenderableObjects/Interfaces/include/IRenderableObject.hpp"


namespace Andromeda::Rendering
{
    class RENDERING_API ISceneLighting
    {
    public:
        virtual ~ISceneLighting();

        // Getters
        virtual const std::unordered_map<int, const PhysicalProperties::DirectionalLight*> GetDirectionalLights() const = 0;
        virtual const std::unordered_map<int, const PhysicalProperties::PointLight*> GetPointLights() const = 0;
        virtual const std::unordered_map<int, PhysicalProperties::LuminousBehavior*>& GetLuminousObjects() const = 0;
    };
}


#endif // ENVIRONMENT__I_SCENE_LIGHTING__HPP