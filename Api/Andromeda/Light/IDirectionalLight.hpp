#ifndef ANDROMEDA__LIGHT_LIGHT__HPP
#define ANDROMEDA__LIGHT_LIGHT__HPP


#include "ILuminousBehavior.hpp"


namespace Andromeda
{
	class IDirectionalLight
		: public ILuminousBehavior
	{
	public:
		virtual ~IDirectionalLight() = default;

		// Getters
		virtual float GetLightOrthographicHalfSize() const = 0;
		virtual float GetLightNearPlane() const = 0;
		virtual float GetLightFarPlane() const = 0;
		virtual const Math::Vec3& GetDirection() const = 0;
		// Setters
		virtual void SetLightOrthographicHalfSize(float halfSize) = 0;
		virtual void SetLightNearPlane(float nearPlane) = 0;
		virtual void SetLightFarPlane(float farPlane) = 0;
		virtual void SetDirection(const Math::Vec3& direction) = 0;
	};
}


#endif // ANDROMEDA__LIGHT_LIGHT__HPP