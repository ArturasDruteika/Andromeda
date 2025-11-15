#ifndef API__CAMERA__I_PERSPECTIVE_CONTROL__HPP
#define API__CAMERA__I_PERSPECTIVE_CONTROL__HPP


#include "LinearAlgebraDataTypes.hpp"


namespace Andromeda
{
	class IPerspectiveControl
    {
    public:
        virtual ~IPerspectiveControl();

		// Getters
		virtual float GetFieldOfViewDegrees() const = 0;
		virtual float GetNearPlane() const = 0;
		virtual float GetFarPlane() const = 0;
		virtual float GetAspect() const = 0;
		virtual const Math::Mat4& GetProjection() const = 0;
		// Setters
		virtual void SetFieldOfViewDegrees(float fovDeg) = 0;
		virtual void SetNearPlane(float nearPlane) = 0;
		virtual void SetFarPlane(float farPlane) = 0;
		virtual void SetAspect(float aspect) = 0;
    };
}


#endif // API__CAMERA__I_PERSPECTIVE_CONTROL__HPP