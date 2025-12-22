#include "../include/SurfaceObject.hpp"


namespace Andromeda::Space
{
    SurfaceObject::SurfaceObject()
		: m_pMaterial{ nullptr }
    {
    }

    SurfaceObject::~SurfaceObject() = default;

    const Andromeda::IMaterial* SurfaceObject::GetMaterial() const
    {
        return m_pMaterial;
    }

    void SurfaceObject::SetMaterial(const Andromeda::IMaterial* material)
    {
        m_pMaterial = material;
    }
}