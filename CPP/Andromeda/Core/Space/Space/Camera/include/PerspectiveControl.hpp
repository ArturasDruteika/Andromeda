#ifndef SPACE__CAMERA__PERSPECTIVE_CONTROL__HPP
#define SPACE__CAMERA__PERSPECTIVE_CONTROL__HPP


#include "../../MacroExports/include/MacroExports.hpp"
#include "Andromeda/Space/Camera/IPerspectiveControl.hpp"
#include "Math/LinearAlgebra/include/LinearAlgebraDataTypes.hpp"


namespace Andromeda::Space
{
	class SPACE_API PerspectiveControl
		: public virtual IPerspectiveControl
	{
	public:
		PerspectiveControl();
		PerspectiveControl(float fovDeg, float nearPlane, float farPlane, float aspect);
		~PerspectiveControl() override;

		// Getters
		float GetFieldOfViewDegrees() const override;
		float GetNearPlane() const override;
		float GetFarPlane() const override;
		float GetAspect() const override;
		const Math::Mat4& GetProjection() const override;
		// Setters
		void SetFieldOfViewDegrees(float fovDeg, bool updateProjection = true) override;
		void SetNearPlane(float nearPlane, bool updateProjection = true) override;
		void SetFarPlane(float farPlane, bool updateProjection = true) override;
		void SetAspect(float aspect, bool updateProjection = true) override;
		
		// Update projection matrix
		void UpdateProjection() override;

	protected:
		float m_fovDeg;
		float m_nearPlane;
		float m_farPlane;
		float m_aspect;
		Math::Mat4 m_projection;
	};
}


#endif // SPACE__CAMERA__PERSPECTIVE_CONTROL__HPP