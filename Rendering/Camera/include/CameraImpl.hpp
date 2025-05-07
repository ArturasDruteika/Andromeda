#ifndef RENDERING__CAMERA_IMPL__HPP
#define RENDERING__CAMERA_IMPL__HPP


#include "Camera.hpp"
#include "glm/glm.hpp"


namespace Andromeda
{
	namespace Rendering
	{
        class Camera::CameraImpl
        {
        public:
            CameraImpl();
            CameraImpl(const Math::Vec3& position, float yawRadians, float pitchRadians);
            ~CameraImpl();

            // Getters
            float GetYaw() const;
            float GetPitch() const;
            float GetRoll() const;
            Math::Mat4 GetViewMatrix() const;
            Math::Vec3 GetPosition() const;
            Math::Vec3 GetForward() const;
            Math::Vec3 GetRight() const;
            Math::Vec3 GetUp() const;
            // Setters
            void SetPosition(const Math::Vec3& position);
            void SetRotation(float yawRadians, float pitchRadians);

            void Move(const Math::Vec3& delta);
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


#endif // RENDERING__CAMERA_IMPL__HPP