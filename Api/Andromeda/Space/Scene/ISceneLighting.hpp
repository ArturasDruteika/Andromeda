#ifndef API__SCENE__I_SCENE_LIGHTING__HPP
#define API__SCENE__I_SCENE_LIGHTING__HPP


#include "../Light/IDirectionalLight.hpp"
#include "../Light/IPointLight.hpp"
#include "../Objects/ILightObject.hpp"
#include <map>


namespace Andromeda
{
    class ISceneLighting
    {
    public:
        virtual ~ISceneLighting() = default;

        // Getters
        virtual const std::unordered_map<int, const IDirectionalLight*>& GetDirectionalLights() const = 0;
        virtual const std::unordered_map<int, const IPointLight*>& GetPointLights() const = 0;
        virtual const std::unordered_map<int, const ILightObject*>& GetLightObjects() const = 0;
    };
}


#endif // API__SCENE__I_SCENE_LIGHTING__HPP