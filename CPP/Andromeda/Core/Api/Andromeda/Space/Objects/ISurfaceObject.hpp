#ifndef API__OBJECTS__I_SURFACE_OBJECT__HPP
#define API__OBJECTS__I_SURFACE_OBJECT__HPP


#include "../Materials/IMaterial.hpp"


namespace Andromeda
{
    class ISurfaceObject
    {
    public:
        virtual ~ISurfaceObject() = default;

        virtual const IMaterial* GetMaterial() const = 0;
        virtual void SetMaterial(const IMaterial* material) = 0;
    };
}


#endif // API__OBJECTS__I_SURFACE_OBJECT__HPP