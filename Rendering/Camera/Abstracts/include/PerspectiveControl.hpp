#ifndef RENDERING__PERSPECTIVE_CONTROL__HPP
#define RENDERING__PERSPECTIVE_CONTROL__HPP


#include "glm/glm.hpp"


namespace Andromeda::Rendering
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
		const glm::mat4& GetProjection() const;
		// Setters
		void SetFieldOfViewDegrees(float fovDeg);
		void SetNearPlane(float nearPlane);
		void SetFarPlane(float farPlane);
		void SetAspect(float aspect);

	private:
		void UpdateProjection();

	private:
		float m_fovDeg;
		float m_nearPlane;
		float m_farPlane;
		float m_aspect;
		glm::mat4 m_projection;
	};
}


#endif // RENDERING__PERSPECTIVE_CONTROL__HPP