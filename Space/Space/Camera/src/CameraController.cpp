#include "../include/CameraController.hpp"
#include "Math/LinearAlgebra/include/LinearAlgebraOperations.hpp"


namespace Andromeda::Space
{
	CameraController::CameraController(const Math::Vec3& position, const Math::Vec3& targetCoords)
		: CameraView(position, targetCoords)
		, m_distance{ Math::LinAlgOps::Length(position - targetCoords) }
		, m_orientation{ Math::Quaternion(1.0f, 0.0f, 0.0f, 0.0f) }
	{
	}

    CameraController::~CameraController() = default;

    void CameraController::Rotate(float yaw, float pitch, float roll)
    {
        // Get camera local axis
        Math::Vec3 right = Math::QuaternionOps::Rotate(m_orientation, Math::Vec3(1, 0, 0));
        Math::Vec3 up = Math::QuaternionOps::Rotate(m_orientation, Math::Vec3(0, 1, 0));
        Math::Vec3 forward = Math::QuaternionOps::Rotate(m_orientation, Math::Vec3(0, 0, -1));

        if (roll != 0.0f)
        {
            // Roll: rotate around forward
            Math::Quaternion qRoll = Math::QuaternionOps::AngleAxis(roll, forward);
            m_orientation = Math::QuaternionOps::Normalize(Math::QuaternionOps::Multiply(qRoll, m_orientation));
        }
        else
        {
            // Yaw: rotate around up
            Math::Quaternion qYaw = Math::QuaternionOps::AngleAxis(-yaw, up);
            // Pitch: rotate around right
            Math::Quaternion qPitch = Math::QuaternionOps::AngleAxis(-pitch, right);
            m_orientation = Math::QuaternionOps::Normalize(
                Math::QuaternionOps::Multiply(
                    Math::QuaternionOps::Multiply(qYaw, qPitch), m_orientation)
            );
        }

        UpdateDirection();
    }

    void CameraController::Zoom(float deltaDistance)
    {
        float previousDistance = m_distance;

        // Exponential zoom
        float zoomFactor = std::exp(deltaDistance * 0.1f);
        m_distance *= zoomFactor;
        m_distance = Math::LinAlgOps::Clamp(m_distance, 0.01f, 1e6f);

        UpdateDirection();
    }

    void CameraController::SetOnDistanceChange(OnDistanceChange callback)
    {
		// TODO: Implement observer pattern if needed
    }

    void CameraController::UpdateDirection()
    {
        // Forward is -Z in local space (OpenGL convention)
        Math::Vec3 localOffset(0.0f, 0.0f, m_distance);

        Math::Vec3 offset = Math::QuaternionOps::Rotate(m_orientation, localOffset);
        m_position = m_targetCoords + offset;

        m_up = Math::QuaternionOps::Rotate(m_orientation, Math::Vec3(0.0f, 1.0f, 0.0f));

        CalculateViewMatrix();
    }
}
