#include "../include/LightComponent.hpp"


namespace Andromeda::Space
{
    LightComponent::LightComponent(int id, const ILightObject* lightObject)
        : m_id{ id }
        , m_lightObject{ lightObject }
    {
    }

    LightComponent::~LightComponent() = default;

    int LightComponent::GetId() const
    {
        return m_id;
    }

    const ILightObject* LightComponent::GetLightObject() const
    {
        return m_lightObject;
    }
}