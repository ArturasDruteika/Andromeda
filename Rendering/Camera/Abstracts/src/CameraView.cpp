#include "../include/CameraView.hpp"
#include <glm/gtc/matrix_transform.hpp>


#define GLM_ENABLE_EXPERIMENTAL


namespace Andromeda::Rendering
{
	CameraView::CameraView(const glm::vec3& position, const glm::vec3& targetCoords)
		: m_position{ position }
		, m_targetCoords{ targetCoords }
		, m_forward{ glm::normalize(m_targetCoords - m_position) }
		, m_right{ glm::normalize(glm::cross(m_forward, glm::vec3(0.0f, 0.0f, 1.0f))) }
		, m_up{ glm::cross(m_right, m_forward) }
		, m_xAxis{ 1.0f, 0.0f, 0.0f }
		, m_yAxis{ 0.0f, 1.0f, 0.0f }
		, m_zAxis{ 0.0f, 0.0f, 1.0f }
	{
		CalculateViewMatrix();
	}

	CameraView::~CameraView() = default;

	const glm::vec3& CameraView::GetPosition() const
	{
		return m_position;
	}

	const glm::vec3& CameraView::GetTargetCoords() const
	{
		return m_targetCoords;
	}

	const glm::vec3& CameraView::GetForward() const
	{
		return m_forward;
	}

	const glm::vec3& CameraView::GetRight() const
	{
		return m_right;
	}

	const glm::vec3& CameraView::GetUp() const
	{
		return m_up;
	}

	const glm::mat4& CameraView::GetViewMatrix() const
	{
		return m_viewMat;
	}

	void CameraView::SetPosition(const glm::vec3& position)
	{
		m_position = position;
		CalculateViewMatrix();
	}

	void CameraView::SetTargetCoords(const glm::vec3& targetCoords)
	{
		m_targetCoords = targetCoords;
		CalculateViewMatrix();
	}

	void CameraView::CalculateViewMatrix()
	{
		m_viewMat = glm::lookAt(m_position, m_targetCoords, m_up);
	}
}
