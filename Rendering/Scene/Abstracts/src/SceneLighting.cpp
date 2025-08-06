#include "../include/SceneLighting.hpp"
#include "../../../Light/Abstracts/include/Light.hpp"
#include "../../../Light/Abstracts/include/LuminousBehavior.hpp"


namespace Andromeda::Rendering
{
    SceneLighting::SceneLighting() = default;
    SceneLighting::~SceneLighting() = default;

    const std::unordered_map<int, IRenderableObject*>& SceneLighting::GetLuminousObjects() const
    {
        return m_luminousObjects;
    }

    const std::unordered_map<int, const DirectionalLight*> SceneLighting::GetDirectionalLights() const
    {
        return ExtractLightsOfType<DirectionalLight>(LightType::Directional);
    }

    const std::unordered_map<int, const PointLight*> SceneLighting::GetPointLights() const
    {
        return ExtractLightsOfType<PointLight>(LightType::Point);
    }

    // Fixed Template: returns map of POINTERS to TLight
    template <typename TLight>
    std::unordered_map<int, const TLight*> SceneLighting::ExtractLightsOfType(LightType type) const
    {
        std::unordered_map<int, const TLight*> result;

        for (const auto& [id, obj] : m_luminousObjects)
        {
            if (!obj)
                continue;

            LuminousBehavior* luminousBehavior = dynamic_cast<LuminousBehavior*>(obj->GetLightBehavior());
            if (luminousBehavior && luminousBehavior->GetType() == type)
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
    template std::unordered_map<int, const DirectionalLight*> SceneLighting::ExtractLightsOfType<DirectionalLight>(LightType type) const;
    template std::unordered_map<int, const PointLight*> SceneLighting::ExtractLightsOfType<PointLight>(LightType type) const;
}
