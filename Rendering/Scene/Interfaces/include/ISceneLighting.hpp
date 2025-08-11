#ifndef ENVIRONMENT__I_SCENE_LIGHTING__HPP
#define ENVIRONMENT__I_SCENE_LIGHTING__HPP


#include "../../../MacroExports/include/MacroExports.hpp"
#include "pch.hpp"
#include "../../../Light/LightTypes/include/DirectionalLight.hpp"
#include "../../../Light/LightTypes/include/PointLight.hpp"
#include "../../../RenderableObjects/Interfaces/include/IRenderableObject.hpp"


namespace Andromeda::Rendering
{
    class RENDERING_API ISceneLighting
    {
    public:
        virtual ~ISceneLighting();

        // Getters
        virtual const std::unordered_map<int, const DirectionalLight*> GetDirectionalLights() const = 0;
        virtual const std::unordered_map<int, const PointLight*> GetPointLights() const = 0;
        virtual const std::unordered_map<int, LuminousBehavior*>& GetLuminousObjects() const = 0;
    };
}


#endif // ENVIRONMENT__I_SCENE_LIGHTING__HPP