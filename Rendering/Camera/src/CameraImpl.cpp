#include "../include/CameraImpl.hpp"
#include "../../Utils/include/MathUtils.hpp"
#include "Constants.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtx/quaternion.hpp>
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
            , m_orientation{ glm::normalize(glm::quat(glm::vec3(0.0f, -glm::half_pi<float>(), 0.0f))) }
            , m_worldUp{ 0.0f, 1.0f, 0.0f }
            , m_target{ glm::vec3(0.0f) }
            , m_distance{ glm::length(MathUtils::ToGLM(position)) }
        {
            UpdateDirection();
        }

        Camera::CameraImpl::~CameraImpl() = default;

        float Camera::CameraImpl::GetDistance() const
        {
            return m_distance;
        }

        float Camera::CameraImpl::GetYaw() const
        {
            return 0.0f;
        }

        float Camera::CameraImpl::GetPitch() const
        {
            return 0.0f;
        }

        float Camera::CameraImpl::GetRoll() const
        {
            return 0.0f;
        }

        void Camera::CameraImpl::SetRotation(float yawRadians, float pitchRadians)
        {
        }

        Math::Mat4 Camera::CameraImpl::GetViewMatrix() const
        {
            return MathUtils::FromGLM(m_viewMatrix);
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

        void Camera::CameraImpl::SetOrientation(const glm::quat& orientation)
        {
            m_orientation = glm::normalize(orientation);
            UpdateDirection();
        }

        void Camera::CameraImpl::Move(const Math::Vec3& delta)
        {
            m_position += MathUtils::ToGLM(delta);
        }

        void Camera::CameraImpl::Rotate(float deltaYawRad, float deltaPitchRad)
        {
            glm::vec3 right = glm::normalize(glm::cross(m_forward, m_worldUp));
            glm::quat yaw = glm::angleAxis(deltaYawRad, m_worldUp);
            glm::quat pitch = glm::angleAxis(deltaPitchRad, right);

			spdlog::info("Yaw: {}, Pitch: {}", deltaYawRad, deltaPitchRad);
            m_orientation = glm::normalize(yaw * pitch * m_orientation);
            UpdateDirection();
        }

        void Camera::CameraImpl::UpdateDirection()
        {
            glm::vec3 offset = m_orientation * glm::vec3(0.0f, 0.0f, -m_distance);
            m_position = m_target + offset;
            m_forward = glm::normalize(m_target - m_position);
            m_right = glm::normalize(glm::cross(m_forward, m_worldUp));
            m_up = glm::normalize(glm::cross(m_right, m_forward));
			CalculateViewMatrix();
        }

        void Camera::CameraImpl::CalculateViewMatrix()
        {
            m_viewMatrix = glm::lookAt(m_position, m_position + m_forward, m_up);
        }
    }
}
