#include "../include/Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/common.hpp>


namespace Andromeda
{
    namespace Rendering
    {
        Camera::Camera()
            : Camera(glm::vec3(0.0f, 0.0f, 3.0f), -glm::half_pi<float>(), 0.0f) // -pi/2 yaw = looking along -Z
        {
        }

        Camera::Camera(const glm::vec3& position, float yawRadians, float pitchRadians)
            : m_position{ position }
            , m_yaw{ yawRadians }
            , m_pitch{ pitchRadians }
			, m_roll{ 0.0f }
            , m_worldUp{ 0.0f, 1.0f, 0.0f }
        {
            UpdateDirection();
        }

        float Camera::GetYaw() const
        {
            return m_yaw;
        }

        float Camera::GetPitch() const
        {
            return m_pitch;
        }

        float Camera::GetRoll() const
        {
            return m_roll;
        }

        void Camera::SetPosition(const glm::vec3& position)
        {
            m_position = position;
        }

        void Camera::SetRotation(float yawRadians, float pitchRadians)
        {
            m_yaw = yawRadians;
            m_pitch = glm::clamp(pitchRadians, -glm::half_pi<float>() + 0.01f, glm::half_pi<float>() - 0.01f); // avoid gimbal lock
            UpdateDirection();
        }

        void Camera::Move(const glm::vec3& delta)
        {
            m_position += delta;
        }

        void Camera::Rotate(float deltaYawRad, float deltaPitchRad)
        {
            m_yaw += deltaYawRad;
            m_pitch = glm::clamp(m_pitch + deltaPitchRad, -glm::half_pi<float>() + 0.01f, glm::half_pi<float>() - 0.01f);
            UpdateDirection();
        }

        glm::mat4 Camera::GetViewMatrix() const
        {
            return glm::lookAt(m_position, m_position + m_forward, m_up);
        }

        glm::vec3 Camera::GetPosition() const
        {
            return m_position;
        }

        glm::vec3 Camera::GetForward() const
        {
            return m_forward;
        }

        glm::vec3 Camera::GetRight() const
        {
            return m_right;
        }

        glm::vec3 Camera::GetUp() const
        {
            return m_up;
        }

        void Camera::UpdateDirection()
        {
            glm::vec3 forward{};
            forward.x = cos(m_pitch) * cos(m_yaw);
            forward.y = sin(m_pitch);
            forward.z = cos(m_pitch) * sin(m_yaw);
            m_forward = glm::normalize(forward);

            m_right = glm::normalize(glm::cross(m_forward, m_worldUp));
            m_up = glm::normalize(glm::cross(m_right, m_forward));
        }

	}
}
