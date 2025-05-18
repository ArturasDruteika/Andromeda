#include "../include/CameraInputMapper.hpp"
#include "Trigonometry.hpp"



namespace Andromeda
{
	namespace EngineCore
	{
        CameraInputMapper::CameraInputMapper(Rendering::Camera* pCamera)
            : m_pCamera{ pCamera }
            , m_sensitivity{ 0.3f }
            , m_firstInput{ true }
            , m_lastX{ 0.0 }
            , m_lastY{ 0.0 }
            , m_rotating{ false }
        {
        }

        float CameraInputMapper::GetSensitivity() const
        {
            return m_sensitivity;
        }

        bool CameraInputMapper::GetFirstInput() const
        {
            return m_firstInput;
        }

        double CameraInputMapper::GetLastX() const
        {
            return m_lastX;
        }

        double CameraInputMapper::GetLastY() const
        {
            return m_lastY;
        }

        double CameraInputMapper::GetRotating() const
        {
            return m_rotating;
        }

        void CameraInputMapper::SetSensitivity(float sensitivity)
        {
            m_sensitivity = sensitivity;
        }

        void CameraInputMapper::StartRotating()
        {
            m_rotating = true;
            m_firstInput = true;
        }

        void CameraInputMapper::StopRotating()
        {
            m_rotating = false;
        }

        void CameraInputMapper::MouseMovementToRotation(double xPos, double yPos, bool ctrlHeld)
        {
            if (m_pCamera == nullptr)
                return;

            if (m_firstInput)
            {
                m_lastX = xPos;
                m_lastY = yPos;
                m_firstInput = false;
                return;
            }

            float dx = static_cast<float>(xPos - m_lastX);
            float dy = static_cast<float>(yPos - m_lastY);
            m_lastX = xPos;
            m_lastY = yPos;

            // Ignore if the movement is too large (e.g. sudden jump)
            if (std::abs(dx) > 50.0f || std::abs(dy) > 50.0f)
            {
                return;
            }

            float angleX = dx * m_sensitivity;
            float angleY = dy * m_sensitivity;

            if (ctrlHeld)
            {
                // Only roll, from horizontal drag
                float deltaRoll = -angleX; // In radians
                float deltaRollRad = Math::Trigonometry::Deg2Rad(deltaRoll);
                m_pCamera->Rotate(0.0, 0.0f, deltaRollRad);
            }
            else
            {
                float deltaYaw = angleX;
                float deltaPitch = angleY;
                float deltaYawRad = Math::Trigonometry::Deg2Rad(deltaYaw);
                float deltaPitchlRad = Math::Trigonometry::Deg2Rad(deltaPitch);
                m_pCamera->Rotate(deltaYawRad, deltaPitchlRad, 0.0f);
            }
        }

        void CameraInputMapper::MouseScrollToZoom(float yOffset)
        {
            if (m_pCamera == nullptr)
                return;

            float zoomAmount = yOffset * m_sensitivity;

            // Clamp or process as needed
            m_pCamera->Zoom(zoomAmount);
        }
	}
}