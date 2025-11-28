#ifndef API__SCENE__I_SCENE_LIGHTING__HPP
#define API__SCENE__I_SCENE_LIGHTING__HPP


#include "Space/Light/LightTypes/include/DirectionalLight.hpp"
#include "Space/Light/LightTypes/include/PointLight.hpp"
#include "../Objects/IGeometricObject.hpp"
#include <map>


namespace Andromeda
{
    class ISceneLighting
    {
    public:
        virtual ~ISceneLighting() = default;

        // Getters
        virtual const std::unordered_map<int, const Space::DirectionalLight*> GetDirectionalLights() const = 0;
        virtual const std::unordered_map<int, const Space::PointLight*> GetPointLights() const = 0;
        virtual const std::unordered_map<int, Space::LuminousBehavior*>& GetLuminousObjects() const = 0;
    };
}


#endif // API__SCENE__I_SCENE_LIGHTING__HPP