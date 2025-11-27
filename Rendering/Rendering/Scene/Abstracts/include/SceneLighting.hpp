#ifndef ENVIRONMENT__ABSTRACTS_SCENE_LIGHTING__HPP
#define ENVIRONMENT__ABSTRACTS_SCENE_LIGHTING__HPP


#include "pch.hpp"
#include "Space/Light/Abstracts/include/LuminousBehavior.hpp"
#include "Space/Light/LightTypes/include/DirectionalLight.hpp"
#include "Space/Light/LightTypes/include/PointLight.hpp"
#include "Space/Light/Support/include/LightTypes.hpp"


namespace Andromeda::Rendering
{
    class SceneLighting
    {
    public:
        SceneLighting();
        ~SceneLighting();

        // Getters
        const std::unordered_map<int, const Space::DirectionalLight*> GetDirectionalLights() const;
        const std::unordered_map<int, const Space::PointLight*> GetPointLights() const;
        const std::unordered_map<int, Space::LuminousBehavior*>& GetLuminousObjects() const;

    protected:
        std::unordered_map<int, Space::LuminousBehavior*> m_luminousObjects;

    private:
        // Fixed: return map of pointers, not objects
        template <typename TLight>
        std::unordered_map<int, const TLight*> ExtractLightsOfType(Space::LightType type) const;
    };
}

#endif // ENVIRONMENT__ABSTRACTS_SCENE_LIGHTING__HPP
