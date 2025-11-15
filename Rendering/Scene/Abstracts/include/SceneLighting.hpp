#ifndef ENVIRONMENT__ABSTRACTS_SCENE_LIGHTING__HPP
#define ENVIRONMENT__ABSTRACTS_SCENE_LIGHTING__HPP


#include "pch.hpp"
#include "LuminousBehavior.hpp"
#include "../../../RenderableObjects/Interfaces/include/IRenderableObject.hpp"
#include "DirectionalLight.hpp"
#include "PointLight.hpp"
#include "LightTypes.hpp"
#include "LinearAlgebraDataTypes.hpp"


namespace Andromeda::Rendering
{
    class SceneLighting
    {
    public:
        SceneLighting();
        ~SceneLighting();

        // Getters
        const std::unordered_map<int, const PhysicalProperties::DirectionalLight*> GetDirectionalLights() const;
        const std::unordered_map<int, const PhysicalProperties::PointLight*> GetPointLights() const;
        const std::unordered_map<int, PhysicalProperties::LuminousBehavior*>& GetLuminousObjects() const;

    protected:
        std::unordered_map<int, PhysicalProperties::LuminousBehavior*> m_luminousObjects;

    private:
        // Fixed: return map of pointers, not objects
        template <typename TLight>
        std::unordered_map<int, const TLight*> ExtractLightsOfType(PhysicalProperties::LightType type) const;
    };
}

#endif // ENVIRONMENT__ABSTRACTS_SCENE_LIGHTING__HPP
