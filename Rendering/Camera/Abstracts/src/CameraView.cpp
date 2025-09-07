#include "../include/CameraView.hpp"
#include "../../../Utils/include/MathUtils.hpp"
#include <glm/gtc/matrix_transform.hpp>


namespace Andromeda::Rendering
{
	CameraView::CameraView(const glm::vec3& position, const glm::vec3& targetCoords)
		: m_position{ position }
		, m_targetCoords{ targetCoords }
		, m_forward{ glm::normalize(m_targetCoords - m_position) }
		, m_right{ glm::normalize(glm::cross(m_forward, glm::vec3(0.0f, 0.0f, 1.0f))) }
		, m_up{ glm::cross(m_right, m_forward) }
	{
		CalculateViewMatrix();
	}

	CameraView::~CameraView() = default;

	Math::Vec3 CameraView::GetPosition() const
	{
		return MathUtils::FromGLM(m_position);
	}

	Math::Vec3 CameraView::GetTargetCoords() const
	{
		return MathUtils::FromGLM(m_targetCoords);
	}

	Math::Vec3 CameraView::GetForward() const
	{
		return MathUtils::FromGLM(m_forward);
	}

	Math::Vec3 CameraView::GetRight() const
	{
		return MathUtils::FromGLM(m_right);
	}

	Math::Vec3 CameraView::GetUp() const
	{
		return MathUtils::FromGLM(m_up);
	}

	Math::Mat4 CameraView::GetViewMatrix() const
	{
		return MathUtils::FromGLM(m_viewMat);
	}

	void CameraView::SetPosition(const Math::Vec3& position)
	{
		m_position = MathUtils::ToGLM(position);
		CalculateViewMatrix();
	}

	void CameraView::SetTargetCoords(const Math::Vec3& targetCoords)
	{
		m_targetCoords = MathUtils::ToGLM(targetCoords);
		CalculateViewMatrix();
	}

	void CameraView::CalculateViewMatrix()
	{
		m_viewMat = glm::lookAt(m_position, m_targetCoords, m_up);
	}
}
