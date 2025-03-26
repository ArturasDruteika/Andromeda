#include "../include/Camera.hpp"


namespace Andromeda
{
	namespace Rendering
	{
		Camera::Camera()
			: m_viewMatrix{}
			, m_projectionMatrix{}
		{
		}

		Camera::~Camera() = default;

		glm::mat4 Camera::GetViewMatrix() const
		{
			return m_viewMatrix;
		}

		glm::mat4 Camera::GetProjectionMatrix() const
		{
			return m_projectionMatrix;
		}

		void Camera::SetPosition(const glm::vec3& pos)
		{
		}

		void Camera::SetRotation(float pitch, float yaw)
		{
		}

		void Camera::SetProjection(float fov, float aspect, float, float)
		{
		}
	}
}
