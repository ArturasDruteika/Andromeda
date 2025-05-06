#ifndef RENDERING__CAMERA__HPP
#define RENDERING__CAMERA__HPP


#include "glm/glm.hpp"


namespace Andromeda
{
	namespace Rendering
	{
        class Camera
        {
        public:
            Camera();
            Camera(const glm::vec3& position, float yawRadians, float pitchRadians);

            // Getters
            float GetYaw() const;
			float GetPitch() const;
			float GetRoll() const;
            glm::mat4 GetViewMatrix() const;
            glm::vec3 GetPosition() const;
            glm::vec3 GetForward() const;
            glm::vec3 GetRight() const;
            glm::vec3 GetUp() const;
            // Setters
            void SetPosition(const glm::vec3& position);
            void SetRotation(float yawRadians, float pitchRadians);

            void Move(const glm::vec3& delta);
            void Rotate(float deltaYawRad, float deltaPitchRad);

        private:
            void UpdateDirection();

            float m_yaw;    // In radians
            float m_pitch;  // In radians
			float m_roll;   // In radians

            glm::vec3 m_position;
            glm::vec3 m_forward;
            glm::vec3 m_right;
            glm::vec3 m_up;
            glm::vec3 m_worldUp;
        };
	}
}


#endif // RENDERING__CAMERA__HPP