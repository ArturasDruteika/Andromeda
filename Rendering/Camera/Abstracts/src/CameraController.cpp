#include "../include/CameraController.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>


namespace Andromeda::Rendering
{
	CameraController::CameraController()
	{
	}

	CameraController::~CameraController() = default;

    void CameraController::Rotate(float yaw, float pitch, float roll)
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

    void CameraController::Zoom(float deltaDistance)
    {
        float previousDistance = m_distance;

        // Exponential zoom
        float zoomFactor = std::exp(deltaDistance * 0.1f);
        m_distance *= zoomFactor;
        m_distance = glm::clamp(m_distance, 0.01f, 1e6f);

        UpdateDirection();
    }

    void CameraController::UpdateDirection()
    {
        // In Z-up world, forward is Y - we orbit backward along it
        glm::vec3 offset = glm::rotate(m_orientation, glm::vec3(0.0f, 0.0f, m_distance));
        m_position = m_targetCoords + offset;
        m_up = glm::rotate(m_orientation, glm::vec3(0, 1, 0));

        CalculateViewMatrix();
    }
}
