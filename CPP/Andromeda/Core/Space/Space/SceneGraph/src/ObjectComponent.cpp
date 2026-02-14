#include "../include/ObjectComponent.hpp"


namespace Andromeda::Space
{
    ObjectComponent::ObjectComponent(int id, IGeometricObject* object)
        : m_id{ id }
        , m_object{ object }
    {
    }

    ObjectComponent::~ObjectComponent() = default;

    int ObjectComponent::GetId() const
    {
        return m_id;
    }

    IGeometricObject* ObjectComponent::GetObject() const
    {
        return m_object;
    }
}