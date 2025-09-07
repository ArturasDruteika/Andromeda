#ifndef RENDERING__I_PERSPECTIVE_CONTROL__HPP
#define RENDERING__I_PERSPECTIVE_CONTROL__HPP


#include "../../../MacroExports/include/MacroExports.hpp"
#include "glm/glm.hpp"


namespace Andromeda::Rendering
{
	class RENDERING_API IPerspectiveControl
    {
    public:
        virtual ~IPerspectiveControl();

		// Getters
		virtual float GetFieldOfViewDegrees() const = 0;
		virtual float GetNearPlane() const = 0;
		virtual float GetFarPlane() const = 0;
		virtual float GetAspect() const = 0;
		virtual const glm::mat4& GetProjection() const = 0;
		// Setters
		virtual void SetFieldOfViewDegrees(float fovDeg) = 0;
		virtual void SetNearPlane(float nearPlane) = 0;
		virtual void SetFarPlane(float farPlane) = 0;
		virtual void SetAspect(float aspect) = 0;
    };
}


#endif // RENDERING__I_PERSPECTIVE_CONTROL__HPP