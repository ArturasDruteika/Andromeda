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
            : m_position{ MathUtils::ToGLM(position) }                      // Camera world position
            , m_yaw{ yawRadians }                                           // -pi/2 to look toward -Z
            , m_pitch{ pitchRadians }                                       // 0 to stay level
            , m_roll{ 0.0f }
            , m_worldUp{ 0.0f, 1.0f, 0.0f }
            , m_target{ glm::vec3(0.0f) }                                   // Look-at center/orbit point
            , m_distance{ glm::length(MathUtils::ToGLM(position)) }         // Distance from target to camera
            , m_forward{ 0.0f, 0.0f, -1.0f }
            , m_right{ 1.0f, 0.0f, 0.0f }
            , m_up{ 0.0f, 1.0f, 0.0f }
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

        float Camera::CameraImpl::GetDistance() const
        {
            return m_distance;
        }

        Math::Mat4 Camera::CameraImpl::GetViewMatrix() const
        {
            //return MathUtils::FromGLM(glm::lookAt(m_position, m_position + m_forward, m_up));
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

        Math::Vec3 Camera::CameraImpl::GetTarget() const
        {
            return MathUtils::FromGLM(m_target);
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
            m_yaw -= deltaYawRad;
            m_pitch += deltaPitchRad; // Apply directly

            // Clamp pitch to avoid flipping
            m_pitch = glm::clamp(
                m_pitch,
                -glm::half_pi<float>() + 0.01f,
                glm::half_pi<float>() - 0.01f
            );

            UpdateDirection();
        }

        void Camera::CameraImpl::UpdateDirection()
        {
            // Spherical to Cartesian conversion
            glm::vec3 offset{};
            offset.x = m_distance * cos(m_pitch) * sin(m_yaw);
            offset.y = m_distance * sin(m_pitch);
            offset.z = m_distance * cos(m_pitch) * cos(m_yaw);

            m_position = m_target + offset;
            m_forward = glm::normalize(m_target - m_position); // Look at target
            m_right = glm::normalize(glm::cross(m_forward, m_worldUp));
            m_up = glm::normalize(glm::cross(m_right, m_forward));
        }
	}
}
