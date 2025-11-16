#ifndef API__SCENE__I_SCENE_LIGHTING__HPP
#define API__SCENE__I_SCENE_LIGHTING__HPP


#include "pch.hpp"
#include "DirectionalLight.hpp"
#include "PointLight.hpp"
#include "../RenderableObjects/IRenderableObject.hpp"


namespace Andromeda
{
    class ISceneLighting
    {
    public:
        virtual ~ISceneLighting();

        // Getters
        virtual const std::unordered_map<int, const PhysicalProperties::DirectionalLight*> GetDirectionalLights() const = 0;
        virtual const std::unordered_map<int, const PhysicalProperties::PointLight*> GetPointLights() const = 0;
        virtual const std::unordered_map<int, PhysicalProperties::LuminousBehavior*>& GetLuminousObjects() const = 0;
    };
}


#endif // API__SCENE__I_SCENE_LIGHTING__HPP