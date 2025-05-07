#include "../include/CameraImpl.hpp"
#include "../../Utils/include/MathUtils.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/common.hpp>


namespace Andromeda
{
    namespace Rendering
    {
        Camera::CameraImpl::CameraImpl()
            : Camera::CameraImpl(Math::Vec3(0.0f, 0.0f, 3.0f), -glm::half_pi<float>(), 0.0f) // -pi/2 yaw = looking along -Z
        {
        }

        Camera::CameraImpl::CameraImpl(const Math::Vec3& position, float yawRadians, float pitchRadians)
            : m_position{ MathUtils::ToGLM(position) }
            , m_yaw{ yawRadians }
            , m_pitch{ pitchRadians }
			, m_roll{ 0.0f }
            , m_worldUp{ 0.0f, 1.0f, 0.0f }
        {
            UpdateDirection();
        }

        Camera::CameraImpl::~CameraImpl() = default;

        float Camera::CameraImpl::GetYaw() const
        {
            return m_yaw;
        }

        float Camera::CameraImpl::GetPitch() const
        {
            return m_pitch;
        }

        float Camera::CameraImpl::GetRoll() const
        {
            return m_roll;
        }

        Math::Mat4 Camera::CameraImpl::GetViewMatrix() const
        {
            return MathUtils::FromGLM(glm::lookAt(m_position, m_position + m_forward, m_up));
        }

        Math::Vec3 Camera::CameraImpl::GetPosition() const
        {
            return MathUtils::FromGLM(m_position);
        }

        Math::Vec3 Camera::CameraImpl::GetForward() const
        {
            return MathUtils::FromGLM(m_forward);
        }

        Math::Vec3 Camera::CameraImpl::GetRight() const
        {
            return MathUtils::FromGLM(m_right);
        }

        Math::Vec3 Camera::CameraImpl::GetUp() const
        {
            return MathUtils::FromGLM(m_up);
        }

        void Camera::CameraImpl::SetPosition(const Math::Vec3& position)
        {
            m_position = MathUtils::ToGLM(position);
        }

        void Camera::CameraImpl::SetRotation(float yawRadians, float pitchRadians)
        {
            m_yaw = yawRadians;
            m_pitch = glm::clamp(pitchRadians, -glm::half_pi<float>() + 0.01f, glm::half_pi<float>() - 0.01f); // avoid gimbal lock
            UpdateDirection();
        }

        void Camera::CameraImpl::Move(const Math::Vec3& delta)
        {
            m_position += MathUtils::ToGLM(delta);
        }

        void Camera::CameraImpl::Rotate(float deltaYawRad, float deltaPitchRad)
        {
            m_yaw += deltaYawRad;
            m_pitch = glm::clamp(m_pitch + deltaPitchRad, -glm::half_pi<float>() + 0.01f, glm::half_pi<float>() - 0.01f);
            UpdateDirection();
        }

        void Camera::CameraImpl::UpdateDirection()
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
