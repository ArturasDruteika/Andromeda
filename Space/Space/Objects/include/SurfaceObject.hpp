#ifndef SPACE__OBJECTS__SURFACE_OBJECT__HPP
#define SPACE__OBJECTS__SURFACE_OBJECT__HPP


#include "Andromeda/Space/Objects/ISurfaceObject.hpp"


namespace Andromeda::Space
{
    class Material;

    class SurfaceObject
        : public virtual ISurfaceObject
    {
    public:
        SurfaceObject();
        ~SurfaceObject() override;

        const IMaterial* GetMaterial() const override;
        void SetMaterial(const IMaterial* material) override;

    private:
        const IMaterial* m_pMaterial;
    };
}

#endif // SPACE__OBJECTS__SURFACE_OBJECT__HPP
