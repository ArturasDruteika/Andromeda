#ifndef ANDROMEDA__LIGHT__I_DIRECTIONAL_LIGHT__HPP
#define ANDROMEDA__LIGHT__I_DIRECTIONAL_LIGHT__HPP

#include "ILight.hpp"
#include "../Objects/ILightObject.hpp"
#include "../Transformations/IRotatable.hpp"
#include "Math/LinearAlgebra/include/LinearAlgebraDataTypes.hpp"

namespace Andromeda
{
    class IDirectionalLight 
		: public virtual ILight
		, public virtual ILightObject
		, public virtual IRotatable
    {
    public:
        virtual ~IDirectionalLight() = default;

        // Shadow / projection parameters (commonly used for directional light shadow maps)
        virtual float GetLightOrthographicHalfSize() const = 0;
        virtual float GetLightNearPlane() const = 0;
        virtual float GetLightFarPlane() const = 0;

        virtual void SetLightOrthographicHalfSize(float halfSize) = 0;
        virtual void SetLightNearPlane(float nearPlane) = 0;
        virtual void SetLightFarPlane(float farPlane) = 0;

        // Direction of the light in world space (should be normalized)
        virtual const Math::Vec3& GetDirection() const = 0;
        virtual void SetDirection(const Math::Vec3& direction) = 0;
    };
}

#endif // ANDROMEDA__LIGHT__I_DIRECTIONAL_LIGHT__HPP
