#include "../include/SceneLighting.hpp"
#include "../../../Light/Abstracts/include/LuminousBehavior.hpp"


namespace Andromeda::Rendering
{
    SceneLighting::SceneLighting() = default;

    SceneLighting::~SceneLighting() = default;

    const std::unordered_map<int, PhysicalProperties::LuminousBehavior*>& SceneLighting::GetLuminousObjects() const
    {
        return m_luminousObjects;
    }

    const std::unordered_map<int, const PhysicalProperties::DirectionalLight*> SceneLighting::GetDirectionalLights() const
    {
        return ExtractLightsOfType<PhysicalProperties::DirectionalLight>(PhysicalProperties::LightType::Directional);
    }

    const std::unordered_map<int, const PhysicalProperties::PointLight*> SceneLighting::GetPointLights() const
    {
        return ExtractLightsOfType<PhysicalProperties::PointLight>(PhysicalProperties::LightType::Point);
    }

    // Fixed Template: returns map of POINTERS to TLight
    template <typename TLight>
    std::unordered_map<int, const TLight*> SceneLighting::ExtractLightsOfType(PhysicalProperties::LightType type) const
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
    template std::unordered_map<int, const PhysicalProperties::DirectionalLight*> SceneLighting::ExtractLightsOfType<PhysicalProperties::DirectionalLight>(PhysicalProperties::LightType type) const;
    template std::unordered_map<int, const PhysicalProperties::PointLight*> SceneLighting::ExtractLightsOfType<PhysicalProperties::PointLight>(PhysicalProperties::LightType type) const;
}
