#ifndef ANDROMEDA__LIGHT__POINT_LIGHT__HPP
#define ANDROMEDA__LIGHT__POINT_LIGHT__HPP


#include "ILight.hpp"
#include "ILuminousBehavior.hpp"
#include "Math/LinearAlgebra/include/LinearAlgebraDataTypes.hpp"


namespace Andromeda
{
	class IPointLight
		: public ILuminousBehavior
	{
	public:
		virtual ~PointLight() = default;

		// Getters
		virtual float GetAttenuationConstant() const = 0;
		virtual float GetAttenuationLinear() const = 0;
		virtual float GetAttenuationQuadratic() const = 0;
		virtual float GetShadowNearPlane() const = 0;
		virtual float GetShadowFarPlane() const = 0;
		virtual const Math::Vec3& GetPosition() const = 0;
		// Setters
		virtual void SetAttenuationConstant(float attenuationConstant) = 0;
		virtual void SetAttenuationLinear(float attenuationLinear) = 0;
		virtual void SetAttenuationQuadratic(float attenuationQuadratic) = 0;
		virtual void SetShadowNearPlane(float shadowNearPlane) = 0;
		virtual void SetShadowFarPlane(float shadowFarPlane) = 0;
		virtual void SetPosition(const Math::Vec3& position) = 0;
	};
}


#endif // ANDROMEDA__LIGHT__POINT_LIGHT__HPP