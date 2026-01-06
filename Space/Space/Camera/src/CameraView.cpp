#include "../include/CameraView.hpp"
#include "Math/LinearAlgebra/include/LinearAlgebraOperations.hpp"


namespace Andromeda::Space
{
	CameraView::CameraView(const Math::Vec3& position, const Math::Vec3& targetCoords)
		: m_position{ position }
		, m_targetCoords{ targetCoords }
		, m_forward{ Math::LinAlgOps::Normalize(m_targetCoords - m_position) }
		, m_right{ Math::LinAlgOps::Normalize(Math::LinAlgOps::Cross(m_forward, Math::Vec3(0.0f, 1.0f, 0.0f))) }
		, m_up{ Math::LinAlgOps::Cross(m_right, m_forward) }
	{
		CalculateViewMatrix();
	}

	CameraView::~CameraView() = default;

	const Math::Vec3& CameraView::GetPosition() const
	{
		return m_position;
	}

	const Math::Vec3& CameraView::GetTargetCoords() const
	{
		return m_targetCoords;
	}

	const Math::Vec3& CameraView::GetForward() const
	{
		return m_forward;
	}

	const Math::Vec3& CameraView::GetRight() const
	{
		return m_right;
	}

	const Math::Vec3& CameraView::GetUp() const
	{
		return m_up;
	}

	const Math::Mat4& CameraView::GetViewMatrix() const
	{
		return m_viewMat;
	}

	void CameraView::SetPosition(const Math::Vec3& position)
	{
		m_position = position;
		CalculateViewMatrix();
	}

	void CameraView::SetTargetCoords(const Math::Vec3& targetCoords)
	{
		m_targetCoords = targetCoords;
		CalculateViewMatrix();
	}

	void CameraView::CalculateViewMatrix()
	{
		m_viewMat = Math::LinAlgOps::LookAt(m_position, m_targetCoords, m_up);
	}
}
