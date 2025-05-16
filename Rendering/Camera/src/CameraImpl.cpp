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
            , m_worldUp{ 0.0f, 0.0f, 1.0f }
            , m_targetCoords{ glm::vec3(0.0f) }
            , m_distance{ glm::length(MathUtils::ToGLM(position)) }
            , m_yaw{ yawRadians }
            , m_pitch{ pitchRadians }
            , m_orientation{ glm::quat(1.0f, 0.0f, 0.0f, 0.0f) }
            , m_xAxis{ 1.0f, 0.0f, 0.0f }
            , m_yAxis{ 0.0f, 1.0f, 0.0f }
            , m_zAxis{ 0.0f, 0.0f, 1.0f }
        {
            // Build initial orientation
            glm::quat yawQuat = glm::angleAxis(m_yaw, glm::vec3(0.0f, 0.0f, 1.0f));  // world Z
            glm::quat pitchQuat = glm::angleAxis(m_pitch, glm::vec3(1.0f, 0.0f, 0.0f)); // local right
            m_orientation = glm::normalize(yawQuat * pitchQuat);

            UpdateDirection();
        }

        Camera::CameraImpl::~CameraImpl() = default;

        float Camera::CameraImpl::GetDistance() const
        {
            return m_distance;
        }

        float Camera::CameraImpl::GetYaw() const
        {
            return m_yaw;
        }

        float Camera::CameraImpl::GetPitch() const
        {
            return m_pitch;
        }

        void Camera::CameraImpl::SetYaw(float yaw)
        {
            m_yaw = yaw;
        }

        void Camera::CameraImpl::SetPitch(float pitch)
        {
            m_pitch = pitch;
        }

        void Camera::CameraImpl::SetRoll(float roll)
        {
            m_roll = roll;
        }

        void Camera::CameraImpl::SetRotation(float yaw, float pitch, float roll)
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
            return MathUtils::FromGLM(m_targetCoords);
        }

        void Camera::CameraImpl::SetPosition(const Math::Vec3& position)
        {
            m_position = MathUtils::ToGLM(position);
        }

        void Camera::CameraImpl::Move(const Math::Vec3& delta)
        {
            m_position += MathUtils::ToGLM(delta);
        }

        void Camera::CameraImpl::Rotate(float yaw, float pitch, float roll)
        {
            m_yaw += yaw;
            m_pitch += pitch;
            m_roll += roll;

            // Get camera local axis
            glm::vec3 right = glm::rotate(m_orientation, glm::vec3(1, 0, 0));
            glm::vec3 up = glm::rotate(m_orientation, glm::vec3(0, 1, 0));
            glm::vec3 forward = glm::rotate(m_orientation, glm::vec3(0, 0, -1));

            if (roll > 0.0f)
            {
                // Roll: rotate around forward
                glm::quat qRoll = glm::angleAxis(roll, forward);
                m_orientation = glm::normalize(qRoll * m_orientation);
            }
            else
            {
                // Yaw: rotate around up
                glm::quat qYaw = glm::angleAxis(-yaw, up);
                // Pitch: rotate around right
                glm::quat qPitch = glm::angleAxis(-pitch, right);
                m_orientation = glm::normalize(qYaw * qPitch * m_orientation);
            }

            UpdateDirection();
        }

        void Camera::CameraImpl::UpdateDirection()
        {
            // In Z-up world, forward is Y — we orbit backward along it
            glm::vec3 offset = glm::rotate(m_orientation, glm::vec3(0.0f, 0.0f, m_distance));
            m_position = m_targetCoords + offset;
            m_up = glm::rotate(m_orientation, glm::vec3(0, 1, 0));
            CalculateViewMatrix();
        }

        void Camera::CameraImpl::CalculateViewMatrix()
        {
            m_viewMatrix = glm::lookAt(m_position, m_targetCoords, m_up);
        }

    }
}
