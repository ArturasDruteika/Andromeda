#include "../include/SceneLighting.hpp"
#include "Space/Light/Abstracts/include/LuminousBehavior.hpp"


namespace Andromeda::Rendering
{
    SceneLighting::SceneLighting() = default;

    SceneLighting::~SceneLighting() = default;

    const std::unordered_map<int, Space::LuminousBehavior*>& SceneLighting::GetLuminousObjects() const
    {
        return m_luminousObjects;
    }

    const std::unordered_map<int, const Space::DirectionalLight*> SceneLighting::GetDirectionalLights() const
    {
        return ExtractLightsOfType<Space::DirectionalLight>(Space::LightType::Directional);
    }

    const std::unordered_map<int, const Space::PointLight*> SceneLighting::GetPointLights() const
    {
        return ExtractLightsOfType<Space::PointLight>(Space::LightType::Point);
    }

    // Fixed Template: returns map of POINTERS to TLight
    template <typename TLight>
    std::unordered_map<int, const TLight*> SceneLighting::ExtractLightsOfType(Space::LightType type) const
    {
        std::unordered_map<int, const TLight*> result;

        for (const auto& [id, obj] : m_luminousObjects)
        {
            if (obj && obj->GetType() == type)
            {
                if (auto* casted = dynamic_cast<const TLight*>(obj)) // cast to const TLight*
                {
                    result.emplace(id, casted);
                }
            }
        }

        return result;
    }


    // Explicit instantiations with pointers (note the asterisk *)
    template std::unordered_map<int, const Space::DirectionalLight*> SceneLighting::ExtractLightsOfType<Space::DirectionalLight>(Space::LightType type) const;
    template std::unordered_map<int, const Space::PointLight*> SceneLighting::ExtractLightsOfType<Space::PointLight>(Space::LightType type) const;
}
