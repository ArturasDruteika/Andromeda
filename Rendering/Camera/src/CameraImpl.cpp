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
            , m_orientation{ glm::quat(1.0f, 0.0f, 0.0f, 0.0f) }
            , m_xAxis{ 1.0f, 0.0f, 0.0f }
            , m_yAxis{ 0.0f, 1.0f, 0.0f }
            , m_zAxis{ 0.0f, 0.0f, 1.0f }
        {
            UpdateDirection();
        }

        Camera::CameraImpl::~CameraImpl() = default;

        float Camera::CameraImpl::GetDistance() const
        {
            return m_distance;
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

        void Camera::CameraImpl::Rotate(float yaw, float pitch, float roll)
        {
            // Get camera local axis
            glm::vec3 right = glm::rotate(m_orientation, glm::vec3(1, 0, 0));
            glm::vec3 up = glm::rotate(m_orientation, glm::vec3(0, 1, 0));
            glm::vec3 forward = glm::rotate(m_orientation, glm::vec3(0, 0, -1));

            if (roll != 0.0f)
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

        void Camera::CameraImpl::Zoom(float deltaDistance)
        {
            float previousDistance = m_distance;

            // Exponential zoom
            float zoomFactor = std::exp(deltaDistance * 0.1f);
            m_distance *= zoomFactor;
            m_distance = glm::clamp(m_distance, 0.01f, 1e6f);

            UpdateDirection();

            // Detect if crossed a multiple of 10
            int prevBucket = static_cast<int>(previousDistance / 10.0f);
            int currBucket = static_cast<int>(m_distance / 10.0f);

            if (prevBucket != currBucket)
            {
                int crossedValue = (deltaDistance > 0.0f) ? (currBucket * 10) : (prevBucket * 10);

                if (m_distance > previousDistance)
                {
                    std::cout << "Crossed " << crossedValue << " from below (zoomed out)\n";
                }
                else
                {
                    std::cout << "Crossed " << crossedValue << " from above (zoomed in)\n";
                }

                m_onCrossedDistanceCallback(m_distance > previousDistance);
            }
        }

        void Camera::CameraImpl::SetOnCrossedDistance(OnCrossedDistance callback)
        {
		    m_onCrossedDistanceCallback = std::move(callback);
		}


        void Camera::CameraImpl::UpdateDirection()
        {
            // In Z-up world, forward is Y - we orbit backward along it
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
