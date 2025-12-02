#ifndef SPACE__CAMERA__PERSPECTIVE_CONTROL__HPP
#define SPACE__CAMERA__PERSPECTIVE_CONTROL__HPP


#include "Math/LinearAlgebra/include/LinearAlgebraDataTypes.hpp"


namespace Andromeda::Space
{
	class PerspectiveControl
	{
	public:
		PerspectiveControl();
		PerspectiveControl(float fovDeg, float nearPlane, float farPlane, float aspect);
		~PerspectiveControl();

		// Getters
		float GetFieldOfViewDegrees() const;
		float GetNearPlane() const;
		float GetFarPlane() const;
		float GetAspect() const;
		const Math::Mat4& GetProjection() const;
		// Setters
		void SetFieldOfViewDegrees(float fovDeg, bool updateProjection = true);
		void SetNearPlane(float nearPlane, bool updateProjection = true);
		void SetFarPlane(float farPlane, bool updateProjection = true);
		void SetAspect(float aspect, bool updateProjection = true);
		void UpdateProjection();

	protected:
		float m_fovDeg;
		float m_nearPlane;
		float m_farPlane;
		float m_aspect;
		Math::Mat4 m_projection;
	};
}


#endif // SPACE__CAMERA__PERSPECTIVE_CONTROL__HPP