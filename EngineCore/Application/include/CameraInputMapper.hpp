#ifndef ENGINECORE__CAMERA_INPUT_MAPPER__HPP
#define ENGINECORE__CAMERA_INPUT_MAPPER__HPP


#include "Camera.hpp"


namespace Andromeda::EngineCore
{
    class CameraInputMapper
    {
    public:
        CameraInputMapper(Rendering::Camera* pCamera);
        ~CameraInputMapper() = default;

        // Getters
        float GetSensitivity() const;
        bool GetFirstInput() const;
        double GetLastX() const;
        double GetLastY() const;
        double GetRotating() const;
        // Setters
        void SetSensitivity(float sensitivity);

        void MouseMovementToRotation(double xPos, double yPos, bool ctrlHeld);
		void MouseScrollToZoom(float yOffset);
        void StartRotating();
        void StopRotating();

    private:
        float m_sensitivity;
        bool m_firstInput;
        double m_lastX;
        double m_lastY;
        bool m_rotating;

        Rendering::Camera* m_pCamera;
    };
}


#endif // ENGINECORE__CAMERA_INPUT_MAPPER__HPP