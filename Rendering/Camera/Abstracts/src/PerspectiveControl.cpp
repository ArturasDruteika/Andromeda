#include "../include/PerspectiveControl.hpp"
#include <glm/gtc/matrix_transform.hpp>


namespace Andromeda::Rendering
{
	PerspectiveControl::PerspectiveControl()
		: m_fovDeg{ 45.0f }
		, m_nearPlane{ 0.1f }
		, m_farPlane{ 1000.0f }
		, m_aspect{ 1.0f }
	{
		UpdateProjection();
	}

	PerspectiveControl::PerspectiveControl(float fovDeg, float nearPlane, float farPlane, float aspect)
		: m_fovDeg{ fovDeg }
		, m_nearPlane{ nearPlane }
		, m_farPlane{ farPlane }
		, m_aspect{ aspect }
	{
		UpdateProjection();
	}

	PerspectiveControl::~PerspectiveControl() = default;

	float PerspectiveControl::GetFieldOfViewDegrees() const
	{
		return m_fovDeg;
	}

	float PerspectiveControl::GetNearPlane() const
	{
		return m_nearPlane;
	}

	float PerspectiveControl::GetFarPlane() const
	{
		return m_farPlane;
	}

	float PerspectiveControl::GetAspect() const
	{
		return m_aspect;
	}

	const glm::mat4& PerspectiveControl::GetProjection() const
	{
		return m_projection;
	}

	void PerspectiveControl::SetFieldOfViewDegrees(float fovDeg)
	{
		m_fovDeg = fovDeg;
	}

	void PerspectiveControl::SetNearPlane(float nearPlane)
	{
		m_nearPlane = nearPlane;
	}

	void PerspectiveControl::SetFarPlane(float farPlane)
	{
		m_farPlane = farPlane;
	}

	void PerspectiveControl::SetAspect(float aspect)
	{
		m_aspect = aspect;
	}

	void PerspectiveControl::UpdateProjection()
	{
		m_projection = glm::infinitePerspective(glm::radians(m_fovDeg), m_aspect, m_nearPlane);
	}
}
