#include "../include/PerspectiveControl.hpp"
#include "Math/LinearAlgebra/include/LinearAlgebraDataTypes.hpp"
#include "Math/LinearAlgebra/include/LinearAlgebraOperations.hpp"
#include "Math/Trigonometry/include/Trigonometry.hpp"


namespace Andromeda::Space
{
	PerspectiveControl::PerspectiveControl()
		: m_fovDeg{ 45.0f }
		, m_nearPlane{ 0.1f }
		, m_farPlane{ 1000.0f }
		, m_aspect{ 1.0f }
		, m_projection{}
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

	const Math::Mat4& PerspectiveControl::GetProjection() const
	{
		return m_projection;
	}

	void PerspectiveControl::SetFieldOfViewDegrees(float fovDeg, bool updateProjection)
	{
		m_fovDeg = fovDeg;
		if (updateProjection)
			UpdateProjection();
	}

	void PerspectiveControl::SetNearPlane(float nearPlane, bool updateProjection)
	{
		m_nearPlane = nearPlane;
		if (updateProjection)
			UpdateProjection();
	}

	void PerspectiveControl::SetFarPlane(float farPlane, bool updateProjection)
	{
		m_farPlane = farPlane;
		if (updateProjection)
			UpdateProjection();
	}

	void PerspectiveControl::SetAspect(float aspect, bool updateProjection)
	{
		m_aspect = aspect;
		if (updateProjection)
			UpdateProjection();
	}

	void PerspectiveControl::UpdateProjection()
	{
		m_projection = Math::LinAlgOps::Perspective(
			Math::Trigonometry::Deg2Rad(m_fovDeg), 
			m_aspect, 
			m_nearPlane, 
			m_farPlane
		);
	}
}
